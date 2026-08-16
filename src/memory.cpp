#include "include/pch.h"
#include "include/memory.h"
#include "include/games.h"
#include <string>
#include <cstring>

DWORD baseAddress = 0;
DWORD chunkSize = 0;

static void ChangeMemory(DWORD baseAddress, int value, DWORD offset1, DWORD offset2, bool msg)
{
	DWORD d, ds;
	DWORD* address = (DWORD*)((*(DWORD*)(baseAddress + offset1)) + offset2);

	if (msg)
	{
		char szTest[10];
		sprintf_s(szTest, "Final address is: %X", address);
		MessageBoxA(NULL, szTest, NULL, NULL);
	}

	//VirtualProtect((LPVOID)address, sizeof(value), PAGE_EXECUTE_READWRITE, &d);
	*(int*)address = value;
	//VirtualProtect((LPVOID)address, sizeof(value), d, &ds);
}

static DWORD FindMemoryPattern(const char* pattern, const char* mask, DWORD startAddress)
{
	DWORD patternLength = (DWORD)strlen(mask);

	// Convert the absolute starting address into an offset within the scan region.
	// Falls back to scanning from the beginning if startAddress is 0 or out of range.
	DWORD startOffset = 0;
	if (startAddress != 0 && startAddress >= baseAddress && startAddress < baseAddress + chunkSize)
	{
		startOffset = startAddress - baseAddress;
	}

	for (DWORD i = startOffset; i < chunkSize - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			found &= mask[j] == '?' || pattern[j] == *(char*)(baseAddress + i + j);
		}

		if (found)
		{
			return (baseAddress + i);
		}
	}

	return NULL;
}

static void WriteValueToMemory(uintptr_t addressToWrite, const char* valueToWrite, int byteNum)
{
	unsigned long oldProtect;

	VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)addressToWrite, valueToWrite, byteNum);
	VirtualProtect((LPVOID)(addressToWrite), byteNum, oldProtect, NULL);
}

#if _DEBUG
std::vector<PatchLogEntry> patchLog;
#endif

DWORD PatchAOB(const char* pattern, const char* mask, const char* valueToWrite, int size, int offset, const char* label, DWORD startAddress)
{
#if !_DEBUG
	(void)label;	// unused outside debug builds -- avoids an unreferenced-parameter warning
#endif

	DWORD address = FindMemoryPattern(pattern, mask, startAddress);
	DWORD addressToWrite = address + offset;

#if _DEBUG
	PatchResult result = PatchResult::NotFound;
#endif

	if (address != 0)
	{
		bool alreadyCorrect = memcmp((void*)addressToWrite, valueToWrite, size) == 0;

		if (!alreadyCorrect)
		{
			WriteValueToMemory(addressToWrite, valueToWrite, size);
		}

#if _DEBUG
		result = alreadyCorrect ? PatchResult::AlreadyCorrect : PatchResult::Patched;
#endif
	}

#if _DEBUG
	patchLog.push_back({ label, result, address });
#endif

	if (address != 0)
	{
		return addressToWrite + size;
	}

	return startAddress;
}

#if _DEBUG
void ShowPatchDebugReport()
{
	int patchedCount = 0, skippedCount = 0, failedCount = 0;
	std::string details;

	for (const auto& entry : patchLog)
	{
		char line[512] = { 0 };

		switch (entry.result)
		{
			case PatchResult::Patched:
				sprintf_s(line, "[OK] %s @ 0x%08X\n", entry.label.c_str(), entry.address);
				patchedCount++;
				break;
			case PatchResult::AlreadyCorrect:
				sprintf_s(line, "[SKIP] %s @ 0x%08X\n", entry.label.c_str(), entry.address);
				skippedCount++;
				break;
			case PatchResult::NotFound:
				sprintf_s(line, "[MISS] %s\n", entry.label.c_str());
				failedCount++;
				break;
		}

		details += line;
	}

	char summary[128];
	sprintf_s(summary, "Patched: %d | Already correct: %d | Not found: %d\n\n", patchedCount, skippedCount, failedCount);

	MessageBoxA(0, (summary + details).c_str(), (currentGameDisplayName + " - Patch Debug Report").c_str(), MB_ICONINFORMATION);
}
#endif

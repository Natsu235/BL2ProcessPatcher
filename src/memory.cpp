#include "include/pch.h"
#include "include/memory.h"
#include <Windows.h>
#include <iostream>

MODULEINFO mInfo = { 0 };
DWORD baseAddress = 0;
DWORD chunckSize = 0;

LPSTR GetProcessFileName()
{
	char szExePath[2048];
	GetModuleFileName(NULL, szExePath, 2048);

	return PathFindFileNameA(szExePath);
}

MODULEINFO GetModuleInfo(char* szModule)
{
	MODULEINFO moduleInfo = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);

	if (hModule == 0)
	{
		return moduleInfo;
	}

	GetModuleInformation(GetCurrentProcess(), hModule, &moduleInfo, sizeof(MODULEINFO));
	return moduleInfo;
}

bool InitializeModule(char* module)
{
	mInfo = GetModuleInfo(module);
	baseAddress = (DWORD)mInfo.lpBaseOfDll;
	chunckSize = (DWORD)mInfo.SizeOfImage;

	return (baseAddress != 0);
}

DWORD FindMemoryPattern(char* pattern, char* mask)
{
	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < chunckSize - patternLength; i++)
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

void WriteValueToMemory(uintptr_t addressToWrite, char* valueToWrite, int byteNum)
{
	unsigned long oldProtect;
	VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)addressToWrite, valueToWrite, byteNum);
	VirtualProtect((LPVOID)(addressToWrite), byteNum, oldProtect, NULL);
}
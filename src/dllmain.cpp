#include "include/pch.h"
#include "include/util.h"
#include "include/memory.h"
#include "include/signatures.h"
#include <Windows.h>
#include <iostream>
#include <tchar.h>

const LPCSTR productName =_T("\\StringFileInfo\\040904b0\\ProductName");
const LPCSTR productVersion = _T("\\StringFileInfo\\040904b0\\ProductVersion");
const LPCSTR configuration = _T(".\\BL2ProcessPatcher.ini");

void ChangeMemory(DWORD baseaddress, int value, DWORD offset1, DWORD offset2, bool msg)
{
	DWORD d, ds;
	DWORD* address = (DWORD*)((*(DWORD*)(baseaddress + offset1)) + offset2);

	if (msg)
	{
		char szTest[10];
		sprintf_s(szTest, "Final address is: %X", address);
		MessageBoxA(NULL, szTest, NULL, NULL);
	}

	//VirtualProtect((LPVOID)adress, sizeof(value), PAGE_EXECUTE_READWRITE, &d);
	*(int*)address = value;
	//VirtualProtect((LPVOID)adress, sizeof(value), d, &ds);
}

void PatchAOB(char* pattern, char* mask, char* valuetowrite, int size, int position)
{
	DWORD address = FindMemoryPattern(pattern, mask);

	//char msg[100];
	//sprintf_s(msg, "Address: %X\nValue to write: %X", address, valuetowrite);
	//MessageBoxA(0, msg, "DEBUG", MB_ICONINFORMATION);

	if (address != 0)
	{
		WriteValueToMemory((address + position), valuetowrite, size);
	}
	//else
	//{
	//	MessageBoxA(0, "Sig Not Found", productName, MB_ICONINFORMATION);
	//}
}

void PatchChecksums(char* processName)
{
	char replacePattern[] = "\x78\x78\x78";
	int size = 3;

	for (const auto& pair : signatures) {
		std::string key = pair.first;
		MemorySignature sig = pair.second;

		char* memoryPattern = (char*)sig.Pattern;
		char* memoryMask = (char*)sig.Mask;
		int position = sig.Position;

		if (GetPrivateProfileInt("General", key.c_str(), 0, configuration) == 1) {
			PatchAOB(memoryPattern, memoryMask, replacePattern, size, position);
		}
	}

	if (strcmp(processName, "BorderlandsPreSequel.exe") == 0)
	{
		for (const auto& pair : tps_signatures) {
			std::string key = pair.first;
			MemorySignature sig = pair.second;

			char* memoryPattern = (char*)sig.Pattern;
			char* memoryMask = (char*)sig.Mask;
			int position = sig.Position;

			if (GetPrivateProfileInt("General", key.c_str(), 0, configuration) == 1) {
				PatchAOB(memoryPattern, memoryMask, replacePattern, size, position);
			}
		}
	}
}

void PatchAdditionalChecksums(char* processName)
{
	int size = 20;  // SHA-1 Hash Length

	if (strcmp(processName, "Borderlands2.exe") == 0)
	{
		for (const auto& pair : bl2_dlc_signatures) {
			std::string dlc = pair.first;
			MemorySignature sig = pair.second;

			char* memoryPattern = (char*)sig.Pattern;
			char* memoryMask = (char*)sig.Mask;
			int position = sig.Position;

			if (GetPrivateProfileInt("DLC", dlc.c_str(), 0, configuration) == 1) {
				std::string hash = CalculateSHA1(_T("..\\update\\DLC\\" + dlc + "\\Compat\\Config\\WillowDlc.ini"));
				if (!hash.empty()) {
					PatchAOB(memoryPattern, memoryMask, &hash[0], size, position);
				}
			}
		}
	}

	if (strcmp(processName, "BorderlandsPreSequel.exe") == 0)
	{
		for (const auto& pair : tps_dlc_signatures) {
			std::string dlc = pair.first;
			MemorySignature sig = pair.second;

			char* memoryPattern = (char*)sig.Pattern;
			char* memoryMask = (char*)sig.Mask;
			int position = sig.Position;

			if (GetPrivateProfileInt("DLC", dlc.c_str(), 0, configuration) == 1) {
				std::string hash = CalculateSHA1(_T("..\\update\\DLC\\" + dlc + "\\Compat\\Config\\WillowDlc.ini"));
				if (!hash.empty()) {
					PatchAOB(memoryPattern, memoryMask, &hash[0], size, position);
				}
			}
		}
	}
}

void PatchConsoleCommands(char* processName)
{
	// Enable console commands (remove 'say')
	char consolePattern[] = "\x73\x00\x61\x00\x79\x00\x20\x00";
	char consoleReplace[] = "\x00\x00\x00\x00\x00\x00\x00\x00";
	char consoleMask[] = "xxxxxxxx";

	if (GetPrivateProfileInt("Console", "EnableConsoleCommands", 0, configuration) == 1) {
		PatchAOB(consolePattern, consoleMask, consoleReplace, 8, 0);
	}

#if _DEBUG  // OUT OF SCOPE

	// Enable developer perks
	char developerPattern[] = "\x16\x06\x58\x01\x04\x28\x04\x3A";
	char developerReplace[] = "\x16\x06\x58\x01\x04\x27\x04\x3A";
	char developerMask[] = "xxxxxxxx";

	if ((FindMemoryPattern(developerPattern, developerMask)) == 0)
	{
		MessageBoxA(0, "Memory pattern not found for developer perks.", productName, MB_ICONINFORMATION);
	}

#endif

	// Remove array size limit
	char arraysizePattern[] = "\x8C\x7B\x00\x00\x00\x8B\x8D\x9C\xEE\xFF\xFF";
	char arraysizeReplace[] = "\x85\x7B\x00\x00\x00\x8B\x8D\x9C\xEE\xFF\xFF";
	char arraysizeMask[] = "xxxxxxxxxxx";

	char arraymessagePattern[] = "\x7C\x7B\x8B\x8D\x94\xEE\xFF\xFF";
	char arraymessageReplace[] = "\x75\x7B\x8B\x8D\x94\xEE\xFF\xFF";
	char arraymessageMask[] = "xxxxxxxx";

	if (GetPrivateProfileInt("Console", "RemoveArraySizeLimit", 0, configuration) == 1) {
		PatchAOB(arraysizePattern, arraysizeMask, arraysizeReplace, 11, 0);
		PatchAOB(arraymessagePattern, arraymessageMask, arraymessageReplace, 8, 0);
	}
}

void PatchMiscellaneous(char* processName)
{
	// Nothing to do.
}

//DWORD WINAPI Patch(LPVOID lpParam) { return 0; }

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		LPSTR processName = GetProcessFileName();
		bool moduleInit = InitializeModule(processName);

		if (moduleInit)
		{
			//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Patch, NULL, 0, NULL);  // No thread required for this script. Operation is performed only once at launch.
			PatchChecksums(processName);
			PatchAdditionalChecksums(processName);
			PatchConsoleCommands(processName);
			PatchMiscellaneous(processName);
		}
		else
		{
			MessageBoxA(0, "Failed to initialize process.", productName, MB_ICONWARNING);
		}
    }

    return TRUE;
}

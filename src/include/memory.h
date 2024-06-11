#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>
#include <Shlwapi.h>

LPSTR GetProcessFileName();
MODULEINFO GetModuleInfo(char* szModule);
bool InitializeModule(char* module);
DWORD FindMemoryPattern(char* pattern, char* mask);
void WriteValueToMemory(uintptr_t addressToWrite, char* valueToWrite, int byteNum);

#endif
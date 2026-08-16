#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <Psapi.h>
#include <Shlwapi.h>

LPSTR GetProcessFileName();
MODULEINFO GetModuleInfo(char* szModule);
bool InitializeModule(char* module);

std::string GetPluginDirectory();
void FirstUpperCase(std::string& str);

#endif // UTIL_H

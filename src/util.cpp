#include "include/pch.h"
#include "include/util.h"
#include "include/memory.h"

MODULEINFO mInfo = { 0 };

LPSTR GetProcessFileName()
{
	static char szExePath[2048];
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
	chunkSize = (DWORD)mInfo.SizeOfImage;

	return (baseAddress != 0);
}

// Returns the absolute path to the folder containing this DLL (e.g. ".../Plugins")
std::string GetPluginDirectory()
{
    char path[MAX_PATH];
    HMODULE hModule = NULL;

    // GetModuleHandleEx with this flag reliably gets the handle of the DLL
    // containing this very function, regardless of what CWD the host process has.
    GetModuleHandleExA(
        GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
        (LPCSTR)&GetPluginDirectory,
        &hModule);

    GetModuleFileNameA(hModule, path, MAX_PATH);

    std::string fullPath(path);
    size_t lastSlash = fullPath.find_last_of("\\/");
    return (lastSlash != std::string::npos) ? fullPath.substr(0, lastSlash) : fullPath;
}

void FirstUpperCase(std::string& str)
{
    if (!str.empty()) {
        str[0] = toupper(str[0]);
    }
}

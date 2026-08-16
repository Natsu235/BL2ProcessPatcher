#include "include/pch.h"
#include "include/util.h"
#include "include/hash.h"
#include "include/memory.h"
#include "include/games.h"
#include "include/signatures.h"
#include <wolfssl/wolfcrypt/sha.h>
#include <tchar.h>
#include <string>
#include <vector>

const LPCSTR productName = _T("\\StringFileInfo\\040904b0\\ProductName");
const LPCSTR productVersion = _T("\\StringFileInfo\\040904b0\\ProductVersion");
const LPCSTR configFile = _T(".\\BL2ProcessPatcher.ini");

LPSTR currentProcessName = GetProcessFileName();
std::string currentGameAlias = ResolveGameAlias(currentProcessName);
std::string currentGameDisplayName = ResolveGameDisplayName(currentGameAlias);

bool AppliesToCurrentGame(const std::vector<std::string>& gameAliases)
{
	if (gameAliases.empty()) return true;	// no restriction -> every supported game

	for (const auto& alias : gameAliases) {
		if (alias == currentGameAlias) return true;
	}

	return false;
}

DWORD PatchConsoleCommands(DWORD startAddress = baseAddress)
{
	DWORD next = startAddress;

	for (const auto& group : consolePatches) {
		if (!AppliesToCurrentGame(group.games)) continue;

		if (GetPrivateProfileInt("Console", group.configKey.c_str(), 0, configFile) == 1) {
			for (const auto& patch : group.patches)
			{
				std::string label = group.configKey;
				std::string mask(patch.pattern.size(), 'x');
				next = PatchAOB(patch.pattern.c_str(), mask.c_str(), patch.replacement.c_str(), (int)mask.size(), 0, label.c_str(), next);
			}
		}
	}

	return next;
}

DWORD FixPackageChecksums(DWORD startAddress = baseAddress)
{
	DWORD next = startAddress;

	// Package checksums don't need to be updated, so we disable them instead.
	char replacePattern[] = "\x78\x78\x78";
	int size = sizeof(replacePattern) - 1;

	std::vector<const std::vector<std::string>*> packageSets{ &packageNames };
	if (currentGameAlias == "TPS") {
		packageSets.push_back(&tps_packageNames);
	}

	for (const auto* packageSet : packageSets) {
		for (const auto& package : *packageSet) {
			if (GetPrivateProfileInt("General", package.c_str(), 0, configFile) == 1)
			{
				std::string packageName = package + packageSuffix;
				Signature sig = BuildSignature(packageName, package.size());

				std::string label = packageName;
				next = PatchAOB(sig.pattern.c_str(), sig.mask.c_str(), replacePattern, size, sig.offset, label.c_str(), next);
			}
		}
	}

	return next;
}

DWORD FixDownloadableContentChecksums(DWORD startAddress = baseAddress)
{
	DWORD next = startAddress;
	int size = SHA_DIGEST_SIZE;	// SHA-1 Hash Length

	std::vector<const std::vector<DlcInfo>*> dlcSets;

	// Borderlands 2 DLCs
	if (currentGameAlias == "BL2") {
		dlcSets.push_back(&bl2_dlcInfo);
	}

	// Borderlands: The Pre-Sequel DLCs
	if (currentGameAlias == "TPS") {
		dlcSets.push_back(&tps_dlcInfo);
	}

	for (const auto* dlcSet : dlcSets) {
		for (const auto& dlc : *dlcSet) {
			if (GetPrivateProfileInt("DLC", dlc.codename.c_str(), 0, configFile) == 1) {
				for (const auto& file : dlc.files)
				{
					std::string pattern = dlc.codename + "__" + file.category + "__" + file.patternFile;
					Signature sig = BuildSignature(pattern);

					std::string categoryFolder = file.category;
					FirstUpperCase(categoryFolder);
					std::string fullPath = categoryFolder + "\\" + file.relativePath;

					std::string hash = ResolveFileHash(dlc.diskFolderName, fullPath);
					if (!hash.empty()) {
						std::string label = pattern;
						next = PatchAOB(sig.pattern.c_str(), sig.mask.c_str(), hash.c_str(), size, sig.offset, label.c_str(), next);
					}
				}
			}
		}
	}

	return next;
}

//DWORD WINAPI Patch(LPVOID lpParam) { return 0; }

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		bool moduleInit = InitializeModule(currentProcessName);

		if (moduleInit)
		{
			DWORD cursor = baseAddress;

			//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Patch, NULL, 0, NULL);	// no thread required for this script,
																					// operation is performed only once at launch.
			cursor = PatchConsoleCommands(cursor);
			cursor = FixPackageChecksums(cursor);
			cursor = FixDownloadableContentChecksums(cursor);

#if _DEBUG
			ShowPatchDebugReport();
#endif
		}
		else
		{
			MessageBoxA(0, "Failed to initialize process.", productName, MB_ICONWARNING);
		}
    }

    return TRUE;
}

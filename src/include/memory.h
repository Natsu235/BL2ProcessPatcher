#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

extern DWORD baseAddress;
extern DWORD chunkSize;

#if _DEBUG
enum class PatchResult { NotFound, AlreadyCorrect, Patched };

struct PatchLogEntry {
    std::string label;
    PatchResult result;
    DWORD address;  // 0 if not found
};

extern std::vector<PatchLogEntry> patchLog;

void ShowPatchDebugReport();
#endif

DWORD PatchAOB(
    const char* pattern,
    const char* mask,
    const char* valueToWrite,
    int size,
    int offset,
    const char* label,
    DWORD startAddress = baseAddress);

#endif // MEMORY_H

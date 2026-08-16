#pragma once

#include "pch.h"
#include <string>
#include <vector>

extern LPSTR currentProcessName;
extern std::string currentGameAlias;
extern std::string currentGameDisplayName;

struct GameInfo {
    std::string alias;
    std::string exeName;
    std::string displayName;
};

static const std::vector<GameInfo> supportedGames
{
    { "BL2", "Borderlands2.exe", "Borderlands 2" },
    { "TPS", "BorderlandsPreSequel.exe", "Borderlands: The Pre-Sequel" },
    { "AODK", "TinyTina.exe", "Tiny Tina's Assault on Dragon Keep" },
};

// Resolves the current process's alias (e.g. "BL2") from its exe filename.
// Returns an empty string if the current process isn't a recognized game.
inline std::string ResolveGameAlias(const std::string& exeName)
{
    for (const auto& game : supportedGames) {
        if (game.exeName == exeName) return game.alias;
    }

    return "";
}

inline std::string ResolveGameDisplayName(const std::string& alias)
{
    for (const auto& game : supportedGames) {
        if (game.alias == alias) return game.displayName;
    }

    return "";
}

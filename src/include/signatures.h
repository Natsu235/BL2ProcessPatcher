#pragma once

#include <string>
#include <vector>

struct Signature {
    std::string pattern;
    std::string mask;
    int offset;
};

inline Signature BuildSignature(const std::string& pattern, int offset = 0)
{
    Signature sig;

    sig.pattern = pattern;
    sig.mask = std::string(sig.pattern.size(), 'x');
    sig.offset = (offset != 0) ? offset + 1 : (int)sig.pattern.size() + 1;

    return sig;
}

// Shared global package names
static const std::vector<std::string> packageNames {
    "core", "engine", "akaudio", "gfxui", "gameframework", "gearboxframework",
    "ipdrv", "onlinesubsystemsteamworks", "onlinesubsystemepicstore",
    "willowgame", "menumap", "startup", "startup_loc_int"
};

// Package names specific to Borderlands: The Pre-Sequel
static const std::vector<std::string> tps_packageNames {
    "startup_loc_deu", "startup_loc_esn", "startup_loc_fra", "startup_loc_ita",
    "startup_loc_jpn", "startup_loc_kor", "startup_loc_rus"
};

static const std::string packageSuffix = ".upk";

struct DlcFileInfo {
    std::string category;       // "compat" or "lic" -- embedded in the in-memory pattern
    std::string patternFile;    // lowercase filename embedded in the pattern (e.g. "willowdlc.ini")
    std::string relativePath;   // actual on-disk path, relative to "DLC\\<codename>\\<category>"
};

struct DlcInfo {
    std::string codename;       // lowercase -- must match the executable's pattern exactly, byte-for-byte
    std::string diskFolderName; // real on-disk folder casing, e.g. "POPremierClub" -- used for file paths
    std::vector<DlcFileInfo> files;
};

// Borderlands 2 -- DLC file lists, extracted from the executable's checksum table
static const std::vector<DlcInfo> bl2_dlcInfo
{
    // Headhunters 2/3 (Wattle Gobbler & Mercenary Day)
    { "allium", "Allium", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "steam_1.bin", "Licenses\\steam_1.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Ultra HD Texture Pack (Fight for Sanctuary)
    { "anecana", "Anecana", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Fight for Sanctuary
    { "anemone", "Anemone", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "anemone_intro_part1.txt", "Movies\\Anemone_Intro_Part1.txt" },
        { "lic", "anemone_intro_part2.txt", "Movies\\Anemone_Intro_Part2.txt" },
        { "lic", "anemone_outro.txt", "Movies\\Anemone_Outro.txt" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Assault on Dragon Keep
    { "aster", "Aster", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "aster_intro.txt", "Movies\\Aster_Intro.txt" },
        { "lic", "aster_outro.txt", "Movies\\Aster_Outro.txt" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Community Day 2013 Customizations
    { "commday2013", "CommDay2013", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
    }},
    // Headhunter 1 (Bloody Harvest)
    { "flax", "Flax", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Customizations Pack 1
    { "gardenia01", "Gardenia01", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "steam_1.bin", "Licenses\\steam_1.bin" },
        { "lic", "steam_10.bin", "Licenses\\steam_10.bin" },
        { "lic", "steam_11.bin", "Licenses\\steam_11.bin" },
        { "lic", "steam_12.bin", "Licenses\\steam_12.bin" },
        { "lic", "steam_13.bin", "Licenses\\steam_13.bin" },
        { "lic", "steam_14.bin", "Licenses\\steam_14.bin" },
        { "lic", "steam_2.bin", "Licenses\\steam_2.bin" },
        { "lic", "steam_3.bin", "Licenses\\steam_3.bin" },
        { "lic", "steam_4.bin", "Licenses\\steam_4.bin" },
        { "lic", "steam_5.bin", "Licenses\\steam_5.bin" },
        { "lic", "steam_6.bin", "Licenses\\steam_6.bin" },
        { "lic", "steam_7.bin", "Licenses\\steam_7.bin" },
        { "lic", "steam_8.bin", "Licenses\\steam_8.bin" },
        { "lic", "steam_9.bin", "Licenses\\steam_9.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Customizations Pack 2
    { "gardenia04", "Gardenia04", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "steam_1.bin", "Licenses\\steam_1.bin" },
        { "lic", "steam_2.bin", "Licenses\\steam_2.bin" },
        { "lic", "steam_3.bin", "Licenses\\steam_3.bin" },
        { "lic", "steam_4.bin", "Licenses\\steam_4.bin" },
        { "lic", "steam_5.bin", "Licenses\\steam_5.bin" },
        { "lic", "steam_6.bin", "Licenses\\steam_6.bin" },
        { "lic", "steam_7.bin", "Licenses\\steam_7.bin" },
        { "lic", "steam_8.bin", "Licenses\\steam_8.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Customizations Pack 3
    { "gardenia05", "Gardenia05", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "steam_1.bin", "Licenses\\steam_1.bin" },
        { "lic", "steam_2.bin", "Licenses\\steam_2.bin" },
        { "lic", "steam_3.bin", "Licenses\\steam_3.bin" },
        { "lic", "steam_4.bin", "Licenses\\steam_4.bin" },
        { "lic", "steam_5.bin", "Licenses\\steam_5.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Ultimate Vault Hunter Upgrade Pack 1
    { "gladiolus", "Gladiolus", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Campaign of Carnage
    { "iris", "Iris", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "iris_intro.txt", "Movies\\Iris_Intro.txt" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Psycho Pack (Krieg)
    { "lilac", "Lilac", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Ultimate Vault Hunter Upgrade Pack 2 (The Raid on Digistruct Peak)
    { "lobelia", "Lobelia", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Ultimate Loot Chest Customizations
    { "lootchest2", "LootChest2", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
    }},
    // Ultra HD Texture Pack
    { "mancana", "Mancana", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Headhunters 4/5 (Wedding Day Massacre & Son of Crawmerax)
    { "nasturtium", "Nasturtium", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "steam_1.bin", "Licenses\\steam_1.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Pirate's Booty
    { "orchid", "Orchid", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "orchid_intro.txt", "Movies\\Orchid_Intro.txt" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Pre-Sequel Customizations
    { "peony", "Peony", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
    }},
    // Poker Night at the Inventory 2 Customizations
    { "pn2", "PN2", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
    }},
    // Collector's Edition Pre-Order Bonus
    { "pocollectors", "POCollectors", {
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "preorderbonus.txt", "PreorderBonus.txt" },
        { "lic", "willowdlc.ini", "WillowDLC.ini" },
    }},
    // GameStop Pre-Order Bonus
    { "pogamestop", "POGamestop", {
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "preorderbonus.txt", "PreorderBonus.txt" },
        { "lic", "willowdlc.ini", "WillowDLC.ini" },
    }},
    // Premier Club Pre-Order Bonus
    { "popremierclub", "POPremierClub", {
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "seasonpass.txt", "SeasonPass.txt" },
        { "lic", "willowdlc.ini", "WillowDLC.ini" },
    }},
    // Big Game Hunt
    { "sage", "Sage", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "sage_intro.txt", "Movies\\Sage_Intro.txt" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Mechromancer Pack (Gaige)
    { "tulip", "Tulip", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
    }},
};

// Borderlands: The Pre-Sequel -- DLC file lists, extracted from the executable's checksum table
static const std::vector<DlcInfo> tps_dlcInfo
{
    // Ultra HD Texture Pack
    { "ailanthus", "Ailanthus", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Baroness Pack (Aurelia)
    { "crocus", "Crocus", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Shock Drop Slaughter Pit
    { "freesia", "Freesia", {
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "preorderbonus.txt", "PreorderBonus.txt" },
        { "lic", "willowdlc.ini", "WillowDLC.ini" },
    }},
    // UNUSED
    { "maingamerefs", "MainGameRefs", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
    }},
    // Claptastic Voyage & Ultimate Vault Hunter Upgrade Pack 2
    { "marigold", "Marigold", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "ending.txt", "Movies\\Ending.txt" },
        { "lic", "ending_postcredits.txt", "Movies\\Ending_PostCredits.txt" },
        { "lic", "ma_deck13_p.txt", "Movies\\Ma_Deck13_P.txt" },
        { "lic", "ma_finalboss_p.txt", "Movies\\Ma_FinalBoss_P.txt" },
        { "lic", "ma_leftcluster_p.txt", "Movies\\Ma_LeftCluster_P.txt" },
        { "lic", "ma_motherboard_p.txt", "Movies\\Ma_Motherboard_P.txt" },
        { "lic", "ma_nexus_p.txt", "Movies\\Ma_Nexus_P.txt" },
        { "lic", "ma_rightcluster_p.txt", "Movies\\Ma_RightCluster_P.txt" },
        { "lic", "ma_subboss_p.txt", "Movies\\Ma_SubBoss_P.txt" },
        { "lic", "ma_subconscious_p.txt", "Movies\\Ma_Subconscious_P.txt" },
        { "lic", "subboss_p.txt", "Movies\\SubBoss_P.txt" },
        { "lic", "subcon_crash_screen.txt", "Movies\\SUBCON_crash_screen.txt" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Ultimate Vault Hunter Upgrade Pack 1 (The Holodome Onslaught)
    { "petunia", "Petunia", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "willowdlc.ini", "Config\\ConfigInstall\\WillowDlc.ini" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
    // Doppelganger Pack (Jack)
    { "quince", "Quince", {
        { "compat", "willowdlc.ini", "Config\\WillowDlc.ini" },
        { "compat", "contver.bin", "contver.bin" },
        { "lic", "steam_0.bin", "Licenses\\steam_0.bin" },
        { "lic", "contver.bin", "contver.bin" },
    }},
};

// Raw byte-pattern patches (pattern/replacement bytes are literal, not derived)
struct BytePatch {
    std::string pattern;
    std::string replacement;
};

struct BytePatchGroup {
    std::string configKey;          // looked up under the "Console" .ini section
    std::vector<std::string> games; // game aliases (e.g. "BL2") this group applies to; EMPTY = all
    std::vector<BytePatch> patches; // all patches in the group are applied together
};

// Patches are applied in order in memory, so the order of this list matters!
static const std::vector<BytePatchGroup> consolePatches
{
    { "RemoveArraySizeLimit", { "BL2" }, {
        { "\x7E\x05\xB9\x64\x00\x00\x00\x3B\xF9\x0F\x8D", "\x75\x05\xB9\x64\x00\x00\x00\x3B\xF9\x0F\x8D" },
        { "\x8C\x7B\x00\x00\x00\x8B\x8D\x9C\xEE\xFF\xFF", "\x85\x7B\x00\x00\x00\x8B\x8D\x9C\xEE\xFF\xFF" },
    }},
    { "RemoveArraySizeLimit", { "TPS" }, {
        { "\x7E\x05\xB9\x64\x00\x00\x00\x3B\xF9\x0F\x8D", "\x75\x05\xB9\x64\x00\x00\x00\x3B\xF9\x0F\x8D" },
        { "\x7C\x7B\x8B\x8D\x94\xEE\xFF\xFF", "\x75\x7B\x8B\x8D\x94\xEE\xFF\xFF" },
    }},
    { "EnableConsoleCommands", {}, {
        { "\x83\xC4\x0C\x85\xC0\x75\x1A\x6A", "\x83\xC4\x0C\x85\xC0\x90\x90\x6A" },
        { "\x73\x00\x61\x00\x79\x00\x20", "\x00\x00\x00\x00\x00\x00\x00" },
    }},
};

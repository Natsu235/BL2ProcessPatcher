#pragma once
#ifndef HASH_H
#define HASH_H

#include <string>

std::string ResolveFileHash(const std::string& dlc, const std::string& relativeFilePath);

#endif // HASH_H

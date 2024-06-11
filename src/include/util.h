#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <Windows.h>

template<typename T>
std::string ConvertToHex(const T& binaryResult);
std::string ParseStringToHex(std::string hexString);
std::string CalculateMD5(const std::string& filename);
std::string CalculateSHA1(const std::string& filename);

#endif
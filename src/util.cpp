#include "include/pch.h"
#include "include/util.h"
#include <wolfssl/openssl/md5.h>
#include <wolfssl/openssl/sha.h>
#include <wolfssl/openssl/evp.h>
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

template<typename T>
std::string ConvertToHex(const T& binaryResult)
{
    std::ostringstream ss;
    ss << std::uppercase << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < binaryResult.size(); ++i) {
        ss << std::setw(2) << static_cast<unsigned>(binaryResult.at(i));
    }
    return ss.str();
}

std::string ParseStringToHex(std::string hexString)
{
    std::ostringstream ss;
    ss << hexString[0];
    for (unsigned int i = 2; i < hexString.size(); i++) {
        ss << '\\x' << hexString[i];
    }
    return ss.str();
}

std::string GenerateHash(const std::string& filename, const WOLFSSL_EVP_MD* algorithm, std::size_t size)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        return std::string();
    }

    WOLFSSL_EVP_MD_CTX* mdctx = wolfSSL_EVP_MD_CTX_new();
    wolfSSL_EVP_DigestInit(mdctx, algorithm);

    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    while (!file.eof()) {
        file.read(buffer, bufferSize);
        wolfSSL_EVP_DigestUpdate(mdctx, buffer, file.gcount());
    }
    file.close();

    std::vector<uint8_t> result;
    result.resize(size);
    wolfSSL_EVP_DigestFinal_ex(mdctx, result.data(), nullptr);

    wolfSSL_EVP_MD_CTX_free(mdctx);

    return std::string(std::begin(result), std::end(result));
}

// Calculate the MD5 Hash of a given file
std::string CalculateMD5(const std::string& filename)
{
    return GenerateHash(filename, wolfSSL_EVP_md5(), 16);
}

// Calculate the SHA-1 Hash of a given file
std::string CalculateSHA1(const std::string& filename)
{
    return GenerateHash(filename, wolfSSL_EVP_sha1(), 20);
}
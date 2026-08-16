#include "include/pch.h"
#include "include/hash.h"
#include "include/util.h"
#include <wolfssl/openssl/sha.h>
#include <wolfssl/openssl/evp.h>
//#include <iomanip>
//#include <sstream>
#include <fstream>
#include <vector>

#pragma comment(lib, "crypt32")
#pragma comment(lib, "ws2_32.lib")

/*template<typename T>
static std::string ConvertToHex(const T& binaryResult)
{
    std::ostringstream ss;

    ss << std::uppercase << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < binaryResult.size(); ++i) {
        ss << std::setw(2) << static_cast<unsigned>(binaryResult.at(i));
    }

    return ss.str();
}

static std::string ParseStringToHex(std::string hexString)
{
    std::ostringstream ss;

    ss << hexString[0];
    for (unsigned int i = 2; i < hexString.size(); i++) {
        ss << '\\x' << hexString[i];
    }

    return ss.str();
}*/

static std::string GenerateHash(const std::string& fileName, const WOLFSSL_EVP_MD* algorithm, std::size_t size)
{
    std::ifstream file(fileName, std::ios::binary);
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

// Calculate the SHA-1 hash of a given file
static std::string CalculateSHA1(const std::string& fileName)
{
    return GenerateHash(fileName, wolfSSL_EVP_sha1(), SHA_DIGEST_SIZE);
}

std::string ResolveFileHash(const std::string& dlc, const std::string& relativeFilePath)
{
    static const std::string pluginDir = GetPluginDirectory();  // computed once, cached
    
    std::string updatePath = pluginDir + "\\..\\update\\DLC\\" + dlc + "\\" + relativeFilePath;
    std::string originalPath = pluginDir + "\\..\\..\\..\\DLC\\" + dlc + "\\" + relativeFilePath;

    std::string hash = CalculateSHA1(updatePath);
    if (hash.empty()) {
        hash = CalculateSHA1(originalPath);
    }

    return hash;
}

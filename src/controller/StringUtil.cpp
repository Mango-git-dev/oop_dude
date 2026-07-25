#include "StringUtil.h"
#include <cctype>
#include <algorithm>

std::string StringUtil::normalizeName(const std::string& str) {
    std::string result = str;
    bool newWord = true;
    for (size_t i = 0; i < result.length(); ++i) {
        unsigned char ch = static_cast<unsigned char>(result[i]);
        if (std::isspace(ch)) {
            newWord = true;
        } else if (newWord) {
            result[i] = static_cast<char>(std::toupper(ch));
            newWord = false;
        } else {
            result[i] = static_cast<char>(std::tolower(ch));
        }
    }
    return result;
}

std::string StringUtil::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return result;
}

std::string StringUtil::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

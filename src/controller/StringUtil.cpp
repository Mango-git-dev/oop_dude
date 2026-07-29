#include "StringUtil.h"
#include <cctype>
#include <algorithm>
#include <cmath>

std::string StringUtil::normalizeName(const std::string& str) {
    std::string trimmed = trim(str);
    std::string result;
    bool newWord = true;
    bool prevSpace = false;
    for (size_t i = 0; i < trimmed.length(); ++i) {
        unsigned char ch = static_cast<unsigned char>(trimmed[i]);
        if (std::isspace(ch)) {
            if (!prevSpace) {
                result += ' ';
            }
            prevSpace = true;
            newWord = true;
        } else {
            prevSpace = false;
            if (newWord) {
                result += static_cast<char>(std::toupper(ch));
                newWord = false;
            } else {
                result += static_cast<char>(std::tolower(ch));
            }
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

std::string StringUtil::formatCurrency(double soTien) {
    long long tien = static_cast<long long>(std::llround(soTien));

    bool amDau = (tien < 0);
    if (amDau) tien = -tien;

    std::string chuoiSo = std::to_string(tien);
    std::string ketQua;
    int demChuSo = 0;

    // duyet tu trai qua phai
    for (int i = static_cast<int>(chuoiSo.size()) - 1; i >= 0; --i) {
        ketQua = chuoiSo[i] + ketQua;
        demChuSo++;
        if (demChuSo % 3 == 0 && i != 0) {
            ketQua = "." + ketQua;
        }
    }

    if (amDau) ketQua = "-" + ketQua;
    return ketQua;
}

bool StringUtil::containsIgnoreCase(const std::string& str, const std::string& sub) {
    if (sub.empty()) return true;
    std::string strLower = toLower(trim(str));
    std::string subLower = toLower(trim(sub));
    return strLower.find(subLower) != std::string::npos;
}

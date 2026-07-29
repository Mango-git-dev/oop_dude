#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>

class StringUtil {
public:
    static std::string normalizeName(const std::string& str);
    static std::string toLower(const std::string& str);
    static std::string trim(const std::string& str);


    static std::string formatCurrency(double soTien);
    static bool containsIgnoreCase(const std::string& str, const std::string& sub);
};

#endif // STRINGUTIL_H

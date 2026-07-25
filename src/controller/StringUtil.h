#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>

class StringUtil {
public:
    static std::string normalizeName(const std::string& str);
    static std::string toLower(const std::string& str);
    static std::string trim(const std::string& str);
};

#endif // STRINGUTIL_H

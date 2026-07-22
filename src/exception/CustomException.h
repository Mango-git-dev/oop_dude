#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <exception>
#include <string>

class FileException : public std::exception {
private:
    std::string message;
public:
    FileException(const std::string& msg) : message("File Error: " + msg) {}
    
    // Override the what() function
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidDataException : public std::exception {
private:
    std::string message;
public:
    InvalidDataException(const std::string& msg) : message("Invalid Data Error: " + msg) {}
    
    // Override the what() function
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // CUSTOMEXCEPTION_H

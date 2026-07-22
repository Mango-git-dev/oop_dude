#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../model/Xe.h"
#include "../model/HanhKhach.h"
#include "../model/Ve.h"
#include "../model/ChuyenXe.h"
#include <string>

class ConsoleView {
public:
    void showMenu() const;
    void showMessage(const std::string& msg) const;
    void showError(const std::string& err) const;
    
    // Inputs
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;

    // Output Data
    void displayXe(const Xe& xe) const;
    void displayHanhKhach(const HanhKhach& hk) const;
    void displayVe(const Ve& ve) const;
    void displayChuyenXe(const ChuyenXe* cx) const;
};

#endif // CONSOLEVIEW_H

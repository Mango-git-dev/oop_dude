#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../model/Xe.h"
#include "../model/HanhKhach.h"
#include "../model/Ve.h"
#include "../model/ChuyenXe.h"
#include <string>
#include <vector>
#include <map>

class ConsoleView {
public:
    void showMenu() const;
    void showMainMenu() const;
    void showCustomerMenu() const;
    void showManagerMenu() const;

    void showMessage(const std::string& msg) const;
    void showError(const std::string& err) const;
    
    // screen control
    void clearScreen() const;
    bool confirmYN(const std::string& msg) const;
    void pressAnyKey() const;
    
    //input
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;

    // output single item
    void displayXe(const Xe& xe) const;
    void displayHanhKhach(const HanhKhach& hk) const;
    void displayVe(const Ve& ve) const;
    void displayChuyenXe(const ChuyenXe* cx) const;
    
    // display lists - map versions
    void displayDanhSachXe(const std::map<std::string, Xe>& ds) const;
    void displayDanhSachHanhKhach(const std::map<std::string, HanhKhach>& ds) const;
    void displayDanhSachChuyenXe(const std::map<std::string, ChuyenXe*>& ds) const;
    
    // display lists - vector versions (for filtered results)
    void displayDanhSachVe(const std::vector<Ve>& ds) const;
    void displayDanhSachChuyenXe(const std::vector<ChuyenXe*>& ds) const;
    void displayDanhSachChuyenXeChoKhach(const std::vector<ChuyenXe*>& ds, const std::vector<int>& choTrongList) const;
};

#endif // CONSOLEVIEW_H

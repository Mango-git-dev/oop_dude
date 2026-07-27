#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <vector>
#include <map>
#include "../model/Xe.h"
#include "../model/HanhKhach.h"
#include "../model/Ve.h"
#include "../model/ChuyenXe.h"
#include "../view/ConsoleView.h"
#include "XeController.h"
#include "ChuyenXeController.h"
#include "VeController.h"

class MainController {
private:
    std::map<std::string, Xe> danhSachXe;
    std::map<std::string, HanhKhach> danhSachHanhKhach;
    std::vector<Ve> danhSachVe;
    std::map<std::string, ChuyenXe*> danhSachChuyenXe;

    ConsoleView view;
    XeController xeController;
    ChuyenXeController chuyenXeController;
    VeController veController;

    void loadData();
    void saveData() const;

public:
    MainController();
    ~MainController();

    void start();
    void runCustomerMenu();
    void runManagerMenu();
    void thongKeTongQuat();
};

#endif // MAINCONTROLLER_H

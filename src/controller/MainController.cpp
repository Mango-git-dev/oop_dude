#include "MainController.h"
#include "../data/DataManager.h"
#include "StringUtil.h"
#include <iostream>
#include <iomanip>
#include <exception>

MainController::MainController()
    : xeController(danhSachXe, view),
      chuyenXeController(danhSachChuyenXe, danhSachVe, xeController, view),
      veController(danhSachVe, danhSachHanhKhach, danhSachChuyenXe, xeController, view) {
    try {
        loadData();
        chuyenXeController.capNhatSoHanhKhachTatCa();
    } catch (const std::exception& e) {
        view.showError(e.what());
    }
}

MainController::~MainController() {
    saveData();
    for (auto& entry : danhSachChuyenXe) {
        delete entry.second;
    }
}

void MainController::loadData() {
    DataManager::loadAll(danhSachXe, danhSachHanhKhach, danhSachVe, danhSachChuyenXe);
}

void MainController::saveData() const {
    DataManager::saveAll(danhSachXe, danhSachHanhKhach, danhSachVe, danhSachChuyenXe);
}

void MainController::start() {
    bool running = true;
    while (running) {
        try {
            view.showMainMenu();
            int choice = view.getIntInput("");
            switch (choice) {
                case 1:
                    runCustomerMenu();
                    break;
                case 2:
                    runManagerMenu();
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    view.showError("Lua chon khong hop le! Vui long nhap lai.");
                    view.pressAnyKey();
                    break;
            }
            if (running) {
                saveData();
            }
        } catch (const std::exception& e) {
            view.showError(e.what());
            view.pressAnyKey();
        }
    }
    view.clearScreen();
    std::cout << "Cam on ban da su dung he thong! Tam biet.\n";
}

void MainController::runCustomerMenu() {
    bool running = true;
    while (running) {
        try {
            view.showCustomerMenu();
            int choice = view.getIntInput("");
            switch (choice) {
                case 1: veController.datVeKhachHang(); break;
                case 2: veController.traCuuVeKhachHang(); break;
                case 3: veController.huyVeKhachHang(); break;
                case 0: running = false; break;
                default: view.showError("Lua chon khong hop le!"); view.pressAnyKey(); break;
            }
            if (running) saveData();
        } catch (const std::exception& e) {
            view.showError(e.what());
            view.pressAnyKey();
        }
    }
}

void MainController::runManagerMenu() {
    bool running = true;
    while (running) {
        try {
            view.showManagerMenu();
            int choice = view.getIntInput("");
            switch (choice) {
                case 1: xeController.themXe(); break;
                case 2: xeController.xoaXe(); break;
                case 3: xeController.timKiemXe(); break;
                case 4: xeController.suaThongTinXe(); break;
                case 5: xeController.hienThiToanBoXe(); break;
                case 6: chuyenXeController.themChuyen(); break;
                case 7: chuyenXeController.huyChuyen(); break;
                case 8: chuyenXeController.timKiemChuyen(); break;
                case 9: chuyenXeController.suaThongTinChuyen(); break;
                case 10: chuyenXeController.hienThiDanhSachChuyen(); break;
                case 11: chuyenXeController.sapXepChuyen(); break;
                case 12: veController.huyVeQuanLy(); break;
                case 13: veController.timKiemVe(); break;
                case 14: veController.suaThongTinVe(); break;
                case 15: veController.hienThiDanhSachVe(); break;
                case 16: veController.traCuuKhachHang(); break;
                case 17: thongKeTongQuat(); break;
                case 18: chuyenXeController.xemLichTrinhTrongNgay(); break;
                case 19: chuyenXeController.traCuuTaiXe(); break;
                case 0: running = false; break;
                default: view.showError("Lua chon khong hop le!"); view.pressAnyKey(); break;
            }
            if (running) saveData();
        } catch (const std::exception& e) {
            view.showError(e.what());
            view.pressAnyKey();
        }
    }
}

void MainController::thongKeTongQuat() {
    view.clearScreen();
    std::cout << "THONG KE TONG QUAT\n\n";

    std::cout << "  Tong so xe:          " << danhSachXe.size() << "\n";
    std::cout << "  Tong so chuyen xe:   " << danhSachChuyenXe.size() << "\n";
    std::cout << "  Tong so hanh khach:  " << danhSachHanhKhach.size() << "\n";
    std::cout << "  Tong so ve da ban:   " << danhSachVe.size() << "\n";

    double tongDoanhThu = 0;
    for (const auto& entry : danhSachChuyenXe) {
        const auto* cx = entry.second;
        tongDoanhThu += cx->tinhDoanhThu();
    }
    std::cout << "  Tong doanh thu:      " << StringUtil::formatCurrency(tongDoanhThu) << " VND\n";
    view.pressAnyKey();
}

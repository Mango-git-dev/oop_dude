#include "ConsoleView.h"
#include "../exception/CustomException.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <sstream>

void ConsoleView::clearScreen() const {
    system("cls");
}

bool ConsoleView::confirmYN(const std::string& msg) const {
    std::string choice;
    while (true) {
        std::cout << msg << " (Y/N): ";
        std::getline(std::cin, choice);
        if (choice == "Y" || choice == "y") return true;
        if (choice == "N" || choice == "n") return false;
        std::cout << "[ERROR] Vui long nhap Y hoac N.\n";
    }
}

void ConsoleView::pressAnyKey() const {
    std::cout << "\nPress Any Key To Continue. . .";
    std::cin.get();
}

void ConsoleView::showMainMenu() const {
    clearScreen();
    std::cout << "==================================================\n";
    std::cout << "        HE THONG QUAN LY & DAT VE XE BUS          \n";
    std::cout << "==================================================\n";
    std::cout << "  1. UNG DUNG DANH CHO KHACH HANG\n";
    std::cout << "  2. UNG DUNG DANH CHO QUAN LY\n";
    std::cout << "  0. THOAT CHUONG TRINH\n";
    std::cout << "==================================================\n";
    std::cout << "Nhap lua chon: ";
}

void ConsoleView::showCustomerMenu() const {
    clearScreen();
    std::cout << "=================== DICH VU KHACH HANG ===================\n";
    std::cout << "  1. Tra cuu & Dat ve xe\n";
    std::cout << "  2. Tra cuu ve xe da dat\n";
    std::cout << "  3. Huy ve xe da dat\n";
    std::cout << "  0. Quay lai Menu Chinh\n";
    std::cout << "==========================================================\n";
    std::cout << "Nhap lua chon: ";
}

void ConsoleView::showManagerMenu() const {
    clearScreen();
    std::cout << "=================== PORTAL QUAN LY ===================\n";
    std::cout << "[ XE ]\n";
    std::cout << "  1. Them xe moi           2. Xoa xe theo ma\n";
    std::cout << "  3. Tim kiem xe           4. Sua thong tin xe\n";
    std::cout << "  5. Hien thi toan bo xe\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << "[ CHUYEN XE ]\n";
    std::cout << "  6. Them chuyen moi       7. Huy chuyen xe\n";
    std::cout << "  8. Tim kiem chuyen       9. Sua thong tin chuyen\n";
    std::cout << " 10. Hien thi DS chuyen   11. Sap xep chuyen xe\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << "[ VE & KHACH HANG ]\n";
    std::cout << " 12. Huy ve               13. Tim kiem ve\n";
    std::cout << " 14. Sua thong tin ve     15. Hien thi DS ve\n";
    std::cout << " 16. Tra cuu khach hang\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << "[ THONG KE & BAO CAO ]\n";
    std::cout << " 17. Thong ke tong quat   18. Xem lich trinh ngay\n";
    std::cout << " 19. Tra cuu tai xe\n";
    std::cout << "-----------------------------------------------------\n";
    std::cout << "  0. Quay lai Menu Chinh\n";
    std::cout << "=====================================================\n";
    std::cout << "Nhap lua chon: ";
}

void ConsoleView::showMessage(const std::string& msg) const {
    std::cout << "[INFO] " << msg << "\n";
}

void ConsoleView::showError(const std::string& err) const {
    std::cout << "[ERROR] " << err << "\n";
}

int ConsoleView::getIntInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    size_t start = line.find_first_not_of(" \t\r");
    if (start == std::string::npos || line.empty()) {
        throw InvalidDataException("Vui long nhap mot so nguyen, khong de trong.");
    }
    line = line.substr(start);
    std::istringstream iss(line);
    int value;
    char leftover;
    if (!(iss >> value) || (iss >> leftover)) {
        throw InvalidDataException("Nhap sai dinh dang. Vui long nhap so nguyen (vd: 2026).");
    }
    return value;
}

double ConsoleView::getDoubleInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    size_t start = line.find_first_not_of(" \t\r");
    if (start == std::string::npos || line.empty()) {
        throw InvalidDataException("Vui long nhap mot so, khong de trong.");
    }
    line = line.substr(start);
    std::istringstream iss(line);
    double value;
    char leftover;
    if (!(iss >> value) || (iss >> leftover)) {
        throw InvalidDataException("Nhap sai dinh dang. Vui long nhap so (vd: 120.5).");
    }
    return value;
}

std::string ConsoleView::getStringInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void ConsoleView::displayXe(const Xe& xe) const {
    std::cout << "  Bien So: " << xe.getBienSo() 
              << " | Loai Xe: " << xe.getLoaiXe() 
              << " | Suc Chua: " << xe.getSoGhe() << " cho\n";
}

void ConsoleView::displayHanhKhach(const HanhKhach& hk) const {
    std::cout << "  CCCD: " << hk.getCCCD() 
              << " | Ho Ten: " << hk.getTen() 
              << " | SDT: " << hk.getSDT() << "\n";
}

void ConsoleView::displayVe(const Ve& ve) const {
    std::cout << "  Ma Ve: " << ve.getMaVe() 
              << " | Chuyen Xe: " << ve.getMaChuyenXe() 
              << " | CCCD: " << ve.getCCCDHanhKhach() 
              << " | Gia: " << std::fixed << std::setprecision(0) << ve.getGiaTien() << " VND"
              << " | Noi Di: " << ve.getNoiDi()
              << " | Noi Den: " << ve.getNoiDen() << "\n";
}

void ConsoleView::displayChuyenXe(const ChuyenXe* cx) const {
    if (cx) {
        std::cout << "  Ma: " << cx->getMaChuyen() 
                  << " | " << cx->getNoiDi() << " -> " << cx->getNoiDen()
                  << " | Xe: " << cx->getBienSoXe() 
                  << " | " << cx->getKhoangCach() << "km"
                  << " | Ngay: " << cx->getNgayKhoiHanh()
                  << " | Gio: " << cx->getGioKhoiHanh()
                  << " | Tai Xe: " << cx->getTenTaiXe()
                  << " | HK: " << cx->getSoHanhKhach()
                  << " | Gia Ve: " << std::fixed << std::setprecision(0) << cx->tinhGiaVe() << " VND\n";
    }
}

// display 

void ConsoleView::displayDanhSachXe(const std::map<std::string, Xe>& ds) const {
    if (ds.empty()) {
        showMessage("Danh sach xe trong.");
        return;
    }
    std::cout << "\n";
    std::cout << "+-----+----------------+---------------------+----------+\n";
    std::cout << "| STT |    Bien So     |      Loai Xe        | Suc Chua |\n";
    std::cout << "+-----+----------------+---------------------+----------+\n";
    int stt = 1;
    for (const auto& entry : ds) {
        const auto& xe = entry.second;
        std::cout << "| " << std::setw(3) << stt++ << " "
                  << "| " << std::setw(14) << std::left << xe.getBienSo() << " "
                  << "| " << std::setw(19) << std::left << xe.getLoaiXe() << " "
                  << "| " << std::setw(8) << std::right << xe.getSoGhe() << " |\n";
    }
    std::cout << "+-----+----------------+---------------------+----------+\n";
    std::cout << "Tong so xe: " << ds.size() << "\n";
}

void ConsoleView::displayDanhSachHanhKhach(const std::map<std::string, HanhKhach>& ds) const {
    if (ds.empty()) {
        showMessage("Danh sach hanh khach trong.");
        return;
    }
    std::cout << "\n";
    std::cout << "+-----+----------------+----------------------+-------------+\n";
    std::cout << "| STT |     CCCD       |       Ho Ten         |     SDT     |\n";
    std::cout << "+-----+----------------+----------------------+-------------+\n";
    int stt = 1;
    for (const auto& entry : ds) {
        const auto& hk = entry.second;
        std::cout << "| " << std::setw(3) << stt++ << " "
                  << "| " << std::setw(14) << std::left << hk.getCCCD() << " "
                  << "| " << std::setw(20) << std::left << hk.getTen() << " "
                  << "| " << std::setw(11) << std::left << hk.getSDT() << " |\n";
    }
    std::cout << "+-----+----------------+----------------------+-------------+\n";
    std::cout << "Tong so hanh khach: " << ds.size() << "\n";
}

void ConsoleView::displayDanhSachChuyenXe(const std::map<std::string, ChuyenXe*>& ds) const {
    if (ds.empty()) {
        showMessage("Danh sach chuyen xe trong.");
        return;
    }
    std::cout << "\n";
    std::cout << "+-----+------+--------+----------------+----------------+----------+------------+-------+------------------+------+------------------+\n";
    std::cout << "| STT | Loai | Ma     |    Noi Di      |    Noi Den     | KC (km)  |   Ngay     |  Gio  |    Tai Xe        |  HK  |   Gia Ve (VND)   |\n";
    std::cout << "+-----+------+--------+----------------+----------------+----------+------------+-------+------------------+------+------------------+\n";
    int stt = 1;
    for (const auto& entry : ds) {
        const auto* cx = entry.second;
        std::string loai = (cx->getType() == 1) ? "TH" : "VIP";
        std::cout << "| " << std::setw(3) << stt++ << " "
                  << "| " << std::setw(4) << std::left << loai << " "
                  << "| " << std::setw(6) << std::left << cx->getMaChuyen() << " "
                  << "| " << std::setw(14) << std::left << cx->getNoiDi() << " "
                  << "| " << std::setw(14) << std::left << cx->getNoiDen() << " "
                  << "| " << std::setw(8) << std::right << cx->getKhoangCach() << " "
                  << "| " << std::setw(10) << std::left << cx->getNgayKhoiHanh() << " "
                  << "| " << std::setw(5) << std::left << cx->getGioKhoiHanh() << " "
                  << "| " << std::setw(16) << std::left << cx->getTenTaiXe() << " "
                  << "| " << std::setw(4) << std::right << cx->getSoHanhKhach() << " "
                  << "| " << std::setw(16) << std::right << std::fixed << std::setprecision(0) << cx->tinhGiaVe() << " |\n";
    }
    std::cout << "+-----+------+--------+----------------+----------------+----------+------------+-------+------------------+------+------------------+\n";
    std::cout << "Tong so chuyen: " << ds.size() << "\n";
}

void ConsoleView::displayDanhSachVe(const std::vector<Ve>& ds) const {
    if (ds.empty()) {
        showMessage("Danh sach ve trong.");
        return;
    }
    std::cout << "\n";
    std::cout << "+-----+--------+--------+----------------+--------------+----------------+----------------+\n";
    std::cout << "| STT | Ma Ve  | Chuyen |     CCCD       |   Gia (VND)  |    Noi Di      |    Noi Den     |\n";
    std::cout << "+-----+--------+--------+----------------+--------------+----------------+----------------+\n";
    int stt = 1;
    for (const auto& ve : ds) {
        std::cout << "| " << std::setw(3) << stt++ << " "
                  << "| " << std::setw(6) << std::left << ve.getMaVe() << " "
                  << "| " << std::setw(6) << std::left << ve.getMaChuyenXe() << " "
                  << "| " << std::setw(14) << std::left << ve.getCCCDHanhKhach() << " "
                  << "| " << std::setw(12) << std::right << std::fixed << std::setprecision(0) << ve.getGiaTien() << " "
                  << "| " << std::setw(14) << std::left << ve.getNoiDi() << " "
                  << "| " << std::setw(14) << std::left << ve.getNoiDen() << " |\n";
    }
    std::cout << "+-----+--------+--------+----------------+--------------+----------------+----------------+\n";
    std::cout << "Tong so ve: " << ds.size() << "\n";
}

void ConsoleView::displayDanhSachChuyenXe(const std::vector<ChuyenXe*>& ds) const {
    if (ds.empty()) {
        showMessage("Danh sach chuyen xe trong.");
        return;
    }
    std::cout << "\n";
    std::cout << "+-----+------+--------+----------------+----------------+----------+------------+-------+------------------+------+------------------+\n";
    std::cout << "| STT | Loai | Ma     |    Noi Di      |    Noi Den     | KC (km)  |   Ngay     |  Gio  |    Tai Xe        |  HK  |   Gia Ve (VND)   |\n";
    std::cout << "+-----+------+--------+----------------+----------------+----------+------------+-------+------------------+------+------------------+\n";
    int stt = 1;
    for (const auto* cx : ds) {
        std::string loai = (cx->getType() == 1) ? "TH" : "VIP";
        std::cout << "| " << std::setw(3) << stt++ << " "
                  << "| " << std::setw(4) << std::left << loai << " "
                  << "| " << std::setw(6) << std::left << cx->getMaChuyen() << " "
                  << "| " << std::setw(14) << std::left << cx->getNoiDi() << " "
                  << "| " << std::setw(14) << std::left << cx->getNoiDen() << " "
                  << "| " << std::setw(8) << std::right << cx->getKhoangCach() << " "
                  << "| " << std::setw(10) << std::left << cx->getNgayKhoiHanh() << " "
                  << "| " << std::setw(5) << std::left << cx->getGioKhoiHanh() << " "
                  << "| " << std::setw(16) << std::left << cx->getTenTaiXe() << " "
                  << "| " << std::setw(4) << std::right << cx->getSoHanhKhach() << " "
                  << "| " << std::setw(16) << std::right << std::fixed << std::setprecision(0) << cx->tinhGiaVe() << " |\n";
    }
    std::cout << "+-----+------+--------+----------------+----------------+----------+------------+-------+------------------+------+------------------+\n";
    std::cout << "Tong so chuyen: " << ds.size() << "\n";
}

void ConsoleView::displayDanhSachChuyenXeChoKhach(const std::vector<ChuyenXe*>& ds, const std::vector<int>& choTrongList) const {
    if (ds.empty()) {
        showMessage("Hien khong co chuyen xe nao phu hop trong he thong.");
        return;
    }
    std::cout << "\n";
    std::cout << "+-----+------+----------------+----------------+------------+-------+-----------+--------------------+\n";
    std::cout << "| STT | Loai |    Noi Di      |    Noi Den     |   Ngay     |  Gio  | Cho Trong |    Gia Ve (VND)    |\n";
    std::cout << "+-----+------+----------------+----------------+------------+-------+-----------+--------------------+\n";
    for (size_t i = 0; i < ds.size(); ++i) {
        const auto* cx = ds[i];
        std::string loai = (cx->getType() == 1) ? "TH" : "VIP";
        int choTrong = (i < choTrongList.size()) ? choTrongList[i] : -1;
        std::string choStr = (choTrong >= 0) ? std::to_string(choTrong) : "N/A";

        double giaVe = cx->tinhGiaVe();

        std::cout << "| " << std::setw(3) << (i + 1) << " "
                  << "| " << std::setw(4) << std::left << loai << " "
                  << "| " << std::setw(14) << std::left << cx->getNoiDi() << " "
                  << "| " << std::setw(14) << std::left << cx->getNoiDen() << " "
                  << "| " << std::setw(10) << std::left << cx->getNgayKhoiHanh() << " "
                  << "| " << std::setw(5) << std::left << cx->getGioKhoiHanh() << " "
                  << "| " << std::setw(9) << std::right << choStr << " "
                  << "| " << std::setw(14) << std::right << std::fixed << std::setprecision(0) << giaVe << " VND |\n";
    }
    std::cout << "+-----+------+----------------+----------------+------------+-------+-----------+--------------------+\n";
    std::cout << "Tong so chuyen xe: " << ds.size() << "\n";
}

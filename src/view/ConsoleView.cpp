#include "ConsoleView.h"
#include <iostream>
#include <limits> // For cin.ignore
#include <iomanip>

void ConsoleView::showMenu() const {
    std::cout << "========================== MENU CHUONG TRINH ==========================\n";
    std::cout << "|| >> QUAN LY XE                                                     ||\n";
    std::cout << "||    1. Them xe moi               2. Xoa xe theo ma                 ||\n";
    std::cout << "||    3. Tim kiem xe               4. Sua thong tin xe               ||\n";
    std::cout << "||    5. Hien thi toan bo xe                                         ||\n";
    std::cout << "|| >> QUAN LY CHUYEN                                                 ||\n";
    std::cout << "||    6. Them chuyen moi           7. Huy chuyen xe                  ||\n";
    std::cout << "||    8. Tim kiem chuyen xe        9. Sua thong tin chuyen           ||\n";
    std::cout << "||   10. Hien thi danh sach chuyen 11. Sap xep chuyen                ||\n";
    std::cout << "|| >> QUAN LY VE                                                     ||\n";
    std::cout << "||   12. Dat ve                   13. Huy ve                         ||\n";
    std::cout << "||   14. Tim kiem ve              15. Sua thong tin ve               ||\n";
    std::cout << "||   16. Hien thi danh sach ve                                       ||\n";
    std::cout << "|| >> TONG QUAN                                                      ||\n";
    std::cout << "||   17. Thong ke tong quat       18. Xem lich trinh trong ngay      ||\n";
    std::cout << "||   19. Tra cuu tai xe           20. Tra cuu khach hang             ||\n";
    std::cout << "||    0. Thoat chuong trinh                                          ||\n";
    std::cout << "=======================================================================\n";
    std::cout << "Chon chuc nang: ";
}

void ConsoleView::showMessage(const std::string& msg) const {
    std::cout << "[INFO] " << msg << "\n";
}

void ConsoleView::showError(const std::string& err) const {
    std::cout << "[ERROR] " << err << "\n";
}

int ConsoleView::getIntInput(const std::string& prompt) const {
    std::cout << prompt;
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear(); // clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Nhap sai dinh dang. Vui long nhap so nguyen.\n";
        std::cout << prompt;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

double ConsoleView::getDoubleInput(const std::string& prompt) const {
    std::cout << prompt;
    double value;
    while (!(std::cin >> value)) {
        std::cin.clear(); // clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[ERROR] Nhap sai dinh dang. Vui long nhap so.\n";
        std::cout << prompt;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

std::string ConsoleView::getStringInput(const std::string& prompt) const {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

void ConsoleView::displayXe(const Xe& xe) const {
    std::cout << "Xe [BienSo=" << xe.getBienSo() << ", Loai=" << xe.getLoaiXe() << ", SoGhe=" << xe.getSoGhe() << "]\n";
}

void ConsoleView::displayHanhKhach(const HanhKhach& hk) const {
    std::cout << "HanhKhach [CCCD=" << hk.getCCCD() << ", Ten=" << hk.getTen() << ", SDT=" << hk.getSDT() << "]\n";
}

void ConsoleView::displayVe(const Ve& ve) const {
    std::cout << "Ve [MaVe=" << ve.getMaVe() << ", ChuyenXe=" << ve.getMaChuyenXe() << ", HanhKhach=" << ve.getCCCDHanhKhach() << ", Gia=" << std::fixed << std::setprecision(0) << ve.getGiaTien() << "]\n";
}

void ConsoleView::displayChuyenXe(const ChuyenXe* cx) const {
    if (cx) {
        std::cout << "ChuyenXe [Ma=" << cx->getMaChuyen() << ", NoiDi=" << cx->getNoiDi() << ", NoiDen=" << cx->getNoiDen() 
                  << ", Xe=" << cx->getBienSoXe() << ", KhoangCach=" << cx->getKhoangCach() 
                  << "km, Ngay=" << cx->getNgayKhoiHanh() << ", TaiXe=" << cx->getTenTaiXe()
                  << ", DoanhThu=" << std::fixed << std::setprecision(0) << cx->tinhDoanhThu() << " VND]\n";
    }
}

#include "XeController.h"
#include "StringUtil.h"
#include <iostream>
#include <vector>
#include <cctype>

XeController::XeController(std::map<std::string, Xe>& dsXe, const ConsoleView& consoleView)
    : danhSachXe(dsXe), view(consoleView) {}

int XeController::getSucChuaXe(const std::string& bienSo) const {
    auto it = danhSachXe.find(bienSo);
    if (it != danhSachXe.end()) return it->second.getSoGhe();
    return -1;
}

std::string XeController::chonBienSoXe(const std::string& promptMsg) const {
    if (danhSachXe.empty()) {
        view.showMessage("Danh sach xe trong.");
        return "";
    }
    view.displayDanhSachXe(danhSachXe);
    std::vector<std::string> dsBien;
    for (const auto& entry : danhSachXe) {
        dsBien.push_back(entry.first);
    }

    while (true) {
        std::string input = view.getStringInput(promptMsg + " (nhap STT 1-" + std::to_string(dsBien.size()) + ", hoac 0 de huy): ");
        if (input == "0") return "";
        if (input.empty()) continue;

        bool isNum = true;
        for (char c : input) {
            if (!std::isdigit(static_cast<unsigned char>(c))) { isNum = false; break; }
        }
        if (isNum) {
            int stt = std::stoi(input);
            if (stt >= 1 && stt <= (int)dsBien.size()) {
                return dsBien[stt - 1];
            }
        }
        if (danhSachXe.count(input)) {
            return input;
        }
        view.showError("Lua chon hoac bien so xe khong hop le! (Nhap 0 de huy)");
    }
}

void XeController::themXe() {
    view.clearScreen();
    std::cout << "THEM XE MOI\n\n";

    std::string bienSo;
    while (true) {
        bienSo = view.getStringInput("Nhap bien so xe (hoac '0' de huy): ");
        if (bienSo == "0") return;
        if (bienSo.empty()) {
            view.showError("Bien so khong duoc de trong!");
            continue;
        }
        if (danhSachXe.count(bienSo)) {
            auto& xe = danhSachXe.at(bienSo);
            view.showError("Bien so [" + bienSo + "] da ton tai (Loai=" + xe.getLoaiXe() +
                ", SoGhe=" + std::to_string(xe.getSoGhe()) + "). Vui long nhap bien so khac!");
        } else {
            break;
        }
    }

    std::string loai = StringUtil::normalizeName(view.getStringInput("Nhap loai xe: "));

    int ghe;
    while (true) {
        try {
            ghe = view.getIntInput("Nhap suc chua (so ghe): ");
            if (ghe > 0) break;
            view.showError("Suc chua phai lon hon 0! Vui long nhap lai.");
        } catch (const std::exception& e) {
            view.showError(e.what());
        }
    }

    std::cout << "\nThong tin xe moi\n";
    std::cout << "  Bien So: " << bienSo << " | Loai: " << loai << " | Suc Chua: " << ghe << " cho\n";

    if (view.confirmYN("Xac nhan them xe?")) {
        danhSachXe.emplace(bienSo, Xe(bienSo, loai, ghe));
        view.showMessage("Them xe thanh cong!");
    } else {
        view.showMessage("Da huy thao tac them xe.");
    }
    view.pressAnyKey();
}

void XeController::xoaXe() {
    view.clearScreen();
    std::cout << "XOA XE\n\n";

    std::string bienSo = chonBienSoXe("Chon xe can xoa");
    if (bienSo.empty()) return;

    auto it = danhSachXe.find(bienSo);
    if (it == danhSachXe.end()) {
        view.showError("Khong tim thay xe voi bien so [" + bienSo + "]!");
        view.pressAnyKey();
        return;
    }

    std::cout << "\nThong tin xe se xoa\n";
    view.displayXe(it->second);

    if (view.confirmYN("Xac nhan xoa xe nay?")) {
        danhSachXe.erase(it);
        view.showMessage("Xoa xe thanh cong!");
    } else {
        view.showMessage("Da huy thao tac xoa xe.");
    }
    view.pressAnyKey();
}

void XeController::timKiemXe() {
    view.clearScreen();
    std::cout << "TIM KIEM XE\n\n";

    std::string bienSo = view.getStringInput("Nhap bien so xe can tim (hoac '0' de huy): ");
    if (bienSo == "0" || bienSo.empty()) return;

    auto it = danhSachXe.find(bienSo);
    if (it != danhSachXe.end()) {
        std::cout << "\nKet qua tim kiem\n";
        view.displayXe(it->second);
    } else {
        view.showError("Khong tim thay xe voi bien so [" + bienSo + "]!");
    }
    view.pressAnyKey();
}

void XeController::suaThongTinXe() {
    view.clearScreen();
    std::cout << "SUA THONG TIN XE\n\n";

    std::string bienSo = chonBienSoXe("Chon xe can sua");
    if (bienSo.empty()) return;

    auto it = danhSachXe.find(bienSo);
    if (it == danhSachXe.end()) {
        view.showError("Khong tim thay xe voi bien so [" + bienSo + "]!");
        view.pressAnyKey();
        return;
    }

    std::cout << "\nThong tin hien tai\n";
    view.displayXe(it->second);
    std::cout << "\n";

    std::string loai = StringUtil::normalizeName(view.getStringInput("Nhap loai xe moi: "));

    int ghe;
    while (true) {
        try {
            ghe = view.getIntInput("Nhap suc chua moi: ");
            if (ghe > 0) break;
            view.showError("Suc chua phai lon hon 0! Vui long nhap lai.");
        } catch (const std::exception& e) {
            view.showError(e.what());
        }
    }

    std::cout << "\nThong tin moi\n";
    std::cout << "  Bien So: " << bienSo << " | Loai: " << loai << " | Suc Chua: " << ghe << " cho\n";

    if (view.confirmYN("Xac nhan sua thong tin?")) {
        it->second.setLoaiXe(loai);
        it->second.setSoGhe(ghe);
        view.showMessage("Sua thong tin thanh cong!");
    } else {
        view.showMessage("Da huy thao tac sua.");
    }
    view.pressAnyKey();
}

void XeController::hienThiToanBoXe() {
    view.clearScreen();
    std::cout << "DANH SACH TAT CA XE\n";
    view.displayDanhSachXe(danhSachXe);
    view.pressAnyKey();
}

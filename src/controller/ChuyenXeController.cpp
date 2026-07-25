#include "ChuyenXeController.h"
#include "StringUtil.h"
#include "../model/ChuyenXeThuong.h"
#include "../model/ChuyenXeVIP.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

static bool isValidGio(const std::string& gio) {
    if (gio.length() != 5 || gio[2] != ':') return false;
    int h = std::stoi(gio.substr(0, 2));
    int m = std::stoi(gio.substr(3, 2));
    return (h >= 0 && h <= 23 && m >= 0 && m <= 59);
}

ChuyenXeController::ChuyenXeController(std::map<std::string, ChuyenXe*>& dsChuyen, std::vector<Ve>& dsVe, const XeController& xeCtrl, const ConsoleView& consoleView)
    : danhSachChuyenXe(dsChuyen), danhSachVe(dsVe), xeController(xeCtrl), view(consoleView) {}

int ChuyenXeController::demHanhKhachTheoChuyen(const std::string& maChuyen) const {
    int count = 0;
    for (const auto& ve : danhSachVe) {
        if (ve.getMaChuyenXe() == maChuyen) count++;
    }
    return count;
}

void ChuyenXeController::capNhatSoHanhKhachTatCa() {
    for (auto& entry : danhSachChuyenXe) {
        entry.second->setSoHanhKhach(demHanhKhachTheoChuyen(entry.first));
    }
}

std::string ChuyenXeController::generateMaChuyen() const {
    int maxId = 0;
    for (const auto& entry : danhSachChuyenXe) {
        std::string ma = entry.first;
        int idNum = 0;
        for (char c : ma) {
            if (std::isdigit(static_cast<unsigned char>(c))) {
                idNum = idNum * 10 + (c - '0');
            }
        }
        if (idNum > maxId) maxId = idNum;
    }
    int nextId = maxId + 1;
    std::ostringstream ss;
    ss << "CX" << std::setw(2) << std::setfill('0') << nextId;
    return ss.str();
}

std::string ChuyenXeController::chonMaChuyen(const std::string& promptMsg) const {
    if (danhSachChuyenXe.empty()) {
        view.showMessage("Danh sach chuyen xe trong.");
        return "";
    }
    view.displayDanhSachChuyenXe(danhSachChuyenXe);
    std::vector<std::string> dsMa;
    for (const auto& entry : danhSachChuyenXe) {
        dsMa.push_back(entry.first);
    }

    while (true) {
        std::string input = view.getStringInput(promptMsg + " (nhap STT 1-" + std::to_string(dsMa.size()) + ", hoac 0 de huy): ");
        if (input == "0") return "";
        if (input.empty()) continue;

        bool isNum = true;
        for (char c : input) {
            if (!std::isdigit(static_cast<unsigned char>(c))) { isNum = false; break; }
        }
        if (isNum) {
            int stt = std::stoi(input);
            if (stt >= 1 && stt <= (int)dsMa.size()) {
                return dsMa[stt - 1];
            }
        }
        if (danhSachChuyenXe.count(input)) {
            return input;
        }
        view.showError("Lua chon hoac ma chuyen xe khong hop le! (Nhap 0 de huy)");
    }
}

void ChuyenXeController::themChuyen() {
    view.clearScreen();
    std::cout << "THEM CHUYEN XE MOI\n\n";

    std::string ma = generateMaChuyen();
    std::cout << "[INFO] Ma chuyen xe duoc tao tu dong: " << ma << "\n\n";

    int loai;
    while (true) {
        loai = view.getIntInput("Nhap loai chuyen (1-Thuong, 2-VIP, hoac 0 de huy): ");
        if (loai == 0) return;
        if (loai == 1 || loai == 2) break;
        view.showError("Loai chuyen chi la 1 (Thuong) hoac 2 (VIP)! Vui long nhap lai.");
    }

    std::string di = StringUtil::normalizeName(view.getStringInput("Noi di: "));
    std::string den = StringUtil::normalizeName(view.getStringInput("Noi den: "));

    std::string bien = xeController.chonBienSoXe("Chon bien so xe cho chuyen xe");
    if (bien.empty()) return;

    double kc;
    while (true) {
        kc = view.getDoubleInput("Khoang cach (km): ");
        if (kc > 0) break;
        view.showError("Khoang cach phai lon hon 0! Vui long nhap lai.");
    }

    std::string ngay = view.getStringInput("Ngay khoi hanh (DD/MM/YYYY): ");

    std::string gio;
    while (true) {
        gio = view.getStringInput("Gio khoi hanh (HH:MM): ");
        if (isValidGio(gio)) break;
        view.showError("Gio khong hop le! Vui long nhap dung dinh dang HH:MM (vd: 08:30).");
    }

    std::string taiXe = StringUtil::normalizeName(view.getStringInput("Ten tai xe: "));

    if (loai == 1) {
        std::cout << "\nThong tin chuyen xe thuong\n";
        std::cout << "  Ma: " << ma << " | " << di << " -> " << den << " | Xe: " << bien
                  << " | " << kc << "km | Ngay: " << ngay << " | Gio: " << gio << " | TX: " << taiXe << "\n";

        if (view.confirmYN("Xac nhan them chuyen xe?")) {
            danhSachChuyenXe[ma] = new ChuyenXeThuong(ma, di, den, bien, kc, ngay, gio, taiXe);
            view.showMessage("Them chuyen xe thuong thanh cong voi ma: " + ma);
        } else {
            view.showMessage("Da huy thao tac.");
        }
    } else {
        double phuPhi;
        while (true) {
            phuPhi = view.getDoubleInput("Phu phi dich vu VIP: ");
            if (phuPhi >= 0) break;
            view.showError("Phu phi khong the am! Vui long nhap lai.");
        }

        std::cout << "\nThong tin chuyen xe VIP\n";
        std::cout << "  Ma: " << ma << " | " << di << " -> " << den << " | Xe: " << bien
                  << " | " << kc << "km | Ngay: " << ngay << " | Gio: " << gio
                  << " | TX: " << taiXe << " | Phi VIP: " << phuPhi << " VND\n";

        if (view.confirmYN("Xac nhan them chuyen xe VIP?")) {
            danhSachChuyenXe[ma] = new ChuyenXeVIP(ma, di, den, bien, kc, ngay, gio, taiXe, phuPhi);
            view.showMessage("Them chuyen xe VIP thanh cong voi ma: " + ma);
        } else {
            view.showMessage("Da huy thao tac.");
        }
    }
    view.pressAnyKey();
}

void ChuyenXeController::huyChuyen() {
    view.clearScreen();
    std::cout << "HUY CHUYEN XE\n\n";

    std::string ma = chonMaChuyen("Chon chuyen xe can huy");
    if (ma.empty()) return;

    auto it = danhSachChuyenXe.find(ma);
    if (it == danhSachChuyenXe.end()) {
        view.showError("Khong tim thay chuyen xe voi ma [" + ma + "]!");
        view.pressAnyKey();
        return;
    }

    std::cout << "\nThong tin chuyen xe se huy\n";
    view.displayChuyenXe(it->second);

    if (view.confirmYN("Xac nhan huy chuyen xe nay?")) {
        auto itVe = std::remove_if(danhSachVe.begin(), danhSachVe.end(),
            [&](const Ve& ve) { return ve.getMaChuyenXe() == ma; });
        danhSachVe.erase(itVe, danhSachVe.end());

        delete it->second;
        danhSachChuyenXe.erase(it);
        view.showMessage("Huy chuyen va cac ve lien quan thanh cong!");
    } else {
        view.showMessage("Da huy thao tac.");
    }
    view.pressAnyKey();
}

void ChuyenXeController::timKiemChuyen() {
    view.clearScreen();
    std::cout << "TIM KIEM CHUYEN XE\n\n";

    std::string ma = chonMaChuyen("Nhap hoac chon chuyen xe can tim");
    if (ma.empty()) return;

    auto it = danhSachChuyenXe.find(ma);
    if (it != danhSachChuyenXe.end()) {
        std::cout << "\nKet qua tim kiem\n";
        view.displayChuyenXe(it->second);
    } else {
        view.showError("Khong tim thay chuyen xe voi ma [" + ma + "]!");
    }
    view.pressAnyKey();
}

void ChuyenXeController::suaThongTinChuyen() {
    view.clearScreen();
    std::cout << "SUA THONG TIN CHUYEN XE\n\n";

    std::string ma = chonMaChuyen("Chon chuyen xe can sua");
    if (ma.empty()) return;

    auto it = danhSachChuyenXe.find(ma);
    if (it == danhSachChuyenXe.end()) {
        view.showError("Khong tim thay chuyen xe voi ma [" + ma + "]!");
        view.pressAnyKey();
        return;
    }

    ChuyenXe* cx = it->second;
    std::cout << "\nThong tin hien tai\n";
    view.displayChuyenXe(cx);
    std::cout << "\n";

    std::string di = StringUtil::normalizeName(view.getStringInput("Noi di moi: "));
    std::string den = StringUtil::normalizeName(view.getStringInput("Noi den moi: "));

    std::string bien = xeController.chonBienSoXe("Chon bien so xe moi");
    if (bien.empty()) return;

    double kc;
    while (true) {
        kc = view.getDoubleInput("Khoang cach moi (km): ");
        if (kc > 0) break;
        view.showError("Khoang cach phai lon hon 0! Vui long nhap lai.");
    }

    std::string ngay = view.getStringInput("Ngay khoi hanh moi (DD/MM/YYYY): ");

    std::string gio;
    while (true) {
        gio = view.getStringInput("Gio khoi hanh moi (HH:MM): ");
        if (isValidGio(gio)) break;
        view.showError("Gio khong hop le! Vui long nhap dung dinh dang HH:MM.");
    }

    std::string taiXe = StringUtil::normalizeName(view.getStringInput("Tai xe moi: "));

    std::cout << "\nThong tin moi\n";
    std::cout << "  Ma: " << ma << " | " << di << " -> " << den << " | Xe: " << bien
              << " | " << kc << "km | Ngay: " << ngay << " | Gio: " << gio << " | TX: " << taiXe << "\n";

    if (view.confirmYN("Xac nhan sua thong tin?")) {
        cx->setNoiDi(di);
        cx->setNoiDen(den);
        cx->setBienSoXe(bien);
        cx->setKhoangCach(kc);
        cx->setNgayKhoiHanh(ngay);
        cx->setGioKhoiHanh(gio);
        cx->setTenTaiXe(taiXe);
        view.showMessage("Sua thong tin thanh cong!");
    } else {
        view.showMessage("Da huy thao tac sua.");
    }
    view.pressAnyKey();
}

void ChuyenXeController::hienThiDanhSachChuyen() {
    view.clearScreen();
    std::cout << "DANH SACH CHUYEN XE\n";
    view.displayDanhSachChuyenXe(danhSachChuyenXe);
    view.pressAnyKey();
}

void ChuyenXeController::sapXepChuyen() {
    view.clearScreen();
    std::cout << "SAP XEP CHUYEN XE\n";

    std::vector<ChuyenXe*> sorted;
    for (const auto& entry : danhSachChuyenXe) {
        sorted.push_back(entry.second);
    }
    std::sort(sorted.begin(), sorted.end(), [](ChuyenXe* a, ChuyenXe* b) {
        return a->getKhoangCach() < b->getKhoangCach();
    });
    view.showMessage("Da sap xep danh sach chuyen xe theo khoang cach tang dan.");
    view.displayDanhSachChuyenXe(sorted);
    view.pressAnyKey();
}

void ChuyenXeController::traCuuTaiXe() {
    view.clearScreen();
    std::cout << "TRA CUU TAI XE\n\n";

    std::string tenTX = StringUtil::normalizeName(view.getStringInput("Nhap ten tai xe (hoac '0' de huy): "));
    if (tenTX == "0" || tenTX.empty()) return;

    std::vector<ChuyenXe*> filtered;
    for (const auto& entry : danhSachChuyenXe) {
        auto* cx = entry.second;
        if (cx->getTenTaiXe() == tenTX) {
            filtered.push_back(cx);
        }
    }

    if (filtered.empty()) {
        view.showError("Khong tim thay tai xe [" + tenTX + "] hoac tai xe chua co chuyen!");
    } else {
        std::cout << "\nCac chuyen xe cua tai xe " << tenTX << ":\n";
        view.displayDanhSachChuyenXe(filtered);
    }
    view.pressAnyKey();
}

void ChuyenXeController::xemLichTrinhTrongNgay() {
    view.clearScreen();
    std::cout << "LICH TRINH CHUYEN XE TRONG NGAY\n\n";

    std::string ngay = view.getStringInput("Nhap ngay khoi hanh (DD/MM/YYYY, hoac '0' de huy): ");
    if (ngay == "0" || ngay.empty()) return;

    std::vector<ChuyenXe*> filtered;
    for (const auto& entry : danhSachChuyenXe) {
        auto* cx = entry.second;
        if (cx->getNgayKhoiHanh() == ngay) {
            filtered.push_back(cx);
        }
    }

    if (filtered.empty()) {
        view.showError("Khong co chuyen xe nào khoi hanh vao ngay [" + ngay + "]!");
    } else {
        std::cout << "\nDanh sach chuyen xe khoi hanh ngay " << ngay << ":\n";
        view.displayDanhSachChuyenXe(filtered);
    }
    view.pressAnyKey();
}

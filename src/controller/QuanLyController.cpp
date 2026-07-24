#include "QuanLyController.h"
#include "../data/DataManager.h"
#include "../exception/CustomException.h"
#include "../model/ChuyenXeThuong.h"
#include "../model/ChuyenXeVIP.h"
#include <algorithm>
#include <iostream>
#include <cctype>
#include <iomanip>

static bool isValidSDT(const std::string& sdt) {
    if (sdt.length() != 10 && sdt.length() != 11) return false;
    for (char c : sdt) {
        if (!isdigit(c)) return false;
    }
    return true;
}

static bool isValidCCCD(const std::string& cccd) {
    if (cccd.length() != 12) return false;
    for (char c : cccd) {
        if (!isdigit(c)) return false;
    }
    return true;
}

static bool isValidGio(const std::string& gio) {
    if (gio.length() != 5 || gio[2] != ':') return false;
    int h = std::stoi(gio.substr(0, 2));
    int m = std::stoi(gio.substr(3, 2));
    return (h >= 0 && h <= 23 && m >= 0 && m <= 59);
}

int QuanLyController::demHanhKhachTheoChuyen(const std::string& maChuyen) const {
    int count = 0;
    for (const auto& ve : danhSachVe) {
        if (ve.getMaChuyenXe() == maChuyen) count++;
    }
    return count;
}

void QuanLyController::capNhatSoHanhKhachTatCa() {
    for (auto& entry : danhSachChuyenXe) {
        entry.second->setSoHanhKhach(demHanhKhachTheoChuyen(entry.first));
    }
}

int QuanLyController::getSucChuaXe(const std::string& bienSo) const {
    auto it = danhSachXe.find(bienSo);
    if (it != danhSachXe.end()) return it->second.getSoGhe();
    return -1;
}

QuanLyController::QuanLyController() {
    try {
        loadData();
        capNhatSoHanhKhachTatCa();
    } catch (const std::exception& e) {
        view.showError(e.what());
    }
}

QuanLyController::~QuanLyController() {
    saveData();
    for (auto& entry : danhSachChuyenXe) {
        delete entry.second;
    }
}

void QuanLyController::loadData() {
    DataManager::loadAll(danhSachXe, danhSachHanhKhach, danhSachVe, danhSachChuyenXe);
}

void QuanLyController::saveData() const {
    DataManager::saveAll(danhSachXe, danhSachHanhKhach, danhSachVe, danhSachChuyenXe);
}

void QuanLyController::start() {
    bool running = true;
    while (running) {
        view.showMenu();
        int choice = view.getIntInput("");

        try {
            switch (choice) {
                case 1: themXe(); break;
                case 2: xoaXe(); break;
                case 3: timKiemXe(); break;
                case 4: suaThongTinXe(); break;
                case 5: hienThiToanBoXe(); break;
                case 6: themChuyen(); break;
                case 7: huyChuyen(); break;
                case 8: timKiemChuyen(); break;
                case 9: suaThongTinChuyen(); break;
                case 10: hienThiDanhSachChuyen(); break;
                case 11: sapXepChuyen(); break;
                case 12: datVe(); break;
                case 13: huyVe(); break;
                case 14: timKiemVe(); break;
                case 15: suaThongTinVe(); break;
                case 16: hienThiDanhSachVe(); break;
                case 17: thongKeTongQuat(); break;
                case 18: xemLichTrinhTrongNgay(); break;
                case 19: traCuuTaiXe(); break;
                case 20: traCuuKhachHang(); break;
                case 0: running = false; break;
                default: view.showError("Chuc nang khong hop le!");
                         view.pressAnyKey();
            }
            if (running && choice != 0) {
                saveData();
            }
        } catch (const std::exception& e) {
            view.showError(e.what());
            view.pressAnyKey();
        }
    }
    view.clearScreen();
    std::cout << "End App\n";
}

void QuanLyController::themXe() {
    view.clearScreen();
    std::cout << "THEM XE MOI\n\n";

    std::string bienSo;
    while (true) {
        bienSo = view.getStringInput("Nhap bien so xe: ");
        if (bienSo.empty()) {
            view.showError("Bien so khong duoc de trong!");
            continue;
        }
        if (danhSachXe.count(bienSo)) {
            auto& xe = danhSachXe.at(bienSo);
            view.showError("Bien so [" + bienSo + "] da ton tai (Loai=" + xe.getLoaiXe() +
                ", SoGhe=" + std::to_string(xe.getSoGhe()) +
                "). Vui long nhap bien so khac!");
        } else {
            break;
        }
    }

    std::string loai = view.getStringInput("Nhap loai xe: ");

    int ghe;
    while (true) {
        ghe = view.getIntInput("Nhap suc chua (so ghe): ");
        if (ghe > 0) break;
        view.showError("Suc chua phai lon hon 0! Vui long nhap lai.");
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

void QuanLyController::xoaXe() {
    view.clearScreen();
    std::cout << "XOA XE\n\n";

    std::string bienSo = view.getStringInput("Nhap bien so can xoa: ");

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

void QuanLyController::timKiemXe() {
    view.clearScreen();
    std::cout << "TIM KIEM XE\n\n";

    std::string bienSo = view.getStringInput("Nhap bien so can tim: ");

    auto it = danhSachXe.find(bienSo);
    if (it != danhSachXe.end()) {
        std::cout << "\nKet qua tim kiem\n";
        view.displayXe(it->second);
    } else {
        view.showError("Khong tim thay xe voi bien so [" + bienSo + "]!");
    }
    view.pressAnyKey();
}

void QuanLyController::suaThongTinXe() {
    view.clearScreen();
    std::cout << "SUA THONG TIN XE\n\n";

    std::string bienSo = view.getStringInput("Nhap bien so can sua: ");

    auto it = danhSachXe.find(bienSo);
    if (it == danhSachXe.end()) {
        view.showError("Khong tim thay xe voi bien so [" + bienSo + "]!");
        view.pressAnyKey();
        return;
    }

    std::cout << "\nThong tin hien tai\n";
    view.displayXe(it->second);
    std::cout << "\n";

    std::string loai = view.getStringInput("Nhap loai xe moi: ");

    int ghe;
    while (true) {
        ghe = view.getIntInput("Nhap suc chua moi: ");
        if (ghe > 0) break;
        view.showError("Suc chua phai lon hon 0! Vui long nhap lai.");
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

void QuanLyController::hienThiToanBoXe() {
    view.clearScreen();
    std::cout << "DANH SACH TAT CA XE\n";
    view.displayDanhSachXe(danhSachXe);
    view.pressAnyKey();
}

void QuanLyController::themChuyen() {
    view.clearScreen();
    std::cout << "THEM CHUYEN XE MOI\n\n";

    int loai;
    while (true) {
        loai = view.getIntInput("Nhap loai chuyen (1-Thuong, 2-VIP): ");
        if (loai == 1 || loai == 2) break;
        view.showError("Loai chuyen chi la 1 (Thuong) hoac 2 (VIP)! Vui long nhap lai.");
    }

    std::string ma;
    while (true) {
        ma = view.getStringInput("Ma chuyen: ");
        if (ma.empty()) {
            view.showError("Ma chuyen khong duoc de trong!");
            continue;
        }
        if (danhSachChuyenXe.count(ma)) {
            view.showError("Ma chuyen [" + ma + "] da ton tai! Vui long nhap ma khac.");
        } else {
            break;
        }
    }

    std::string di = view.getStringInput("Noi di: ");
    std::string den = view.getStringInput("Noi den: ");

    std::string bien;
    while (true) {
        bien = view.getStringInput("Bien so xe: ");
        if (danhSachXe.count(bien)) break;
        view.showError("Bien so [" + bien + "] khong ton tai trong danh sach xe! Vui long nhap lai.");
    }

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

    std::string taiXe = view.getStringInput("Ten tai xe: ");

    if (loai == 1) {
        std::cout << "\nThong tin chuyen xe thuong\n";
        std::cout << "  Ma: " << ma << " | " << di << " -> " << den << " | Xe: " << bien
                  << " | " << kc << "km | Ngay: " << ngay << " | Gio: " << gio << " | TX: " << taiXe << "\n";

        if (view.confirmYN("Xac nhan them chuyen xe?")) {
            danhSachChuyenXe[ma] = new ChuyenXeThuong(ma, di, den, bien, kc, ngay, gio, taiXe);
            view.showMessage("Them chuyen xe thuong thanh cong!");
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
            view.showMessage("Them chuyen xe VIP thanh cong!");
        } else {
            view.showMessage("Da huy thao tac.");
        }
    }
    view.pressAnyKey();
}

void QuanLyController::huyChuyen() {
    view.clearScreen();
    std::cout << "HUY CHUYEN XE\n\n";

    std::string ma = view.getStringInput("Nhap ma chuyen can huy: ");

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

void QuanLyController::timKiemChuyen() {
    view.clearScreen();
    std::cout << "TIM KIEM CHUYEN XE\n\n";

    std::string ma = view.getStringInput("Nhap ma chuyen can tim: ");

    auto it = danhSachChuyenXe.find(ma);
    if (it != danhSachChuyenXe.end()) {
        std::cout << "\nKet qua tim kiem\n";
        view.displayChuyenXe(it->second);
    } else {
        view.showError("Khong tim thay chuyen xe voi ma [" + ma + "]!");
    }
    view.pressAnyKey();
}

void QuanLyController::suaThongTinChuyen() {
    view.clearScreen();
    std::cout << "SUA THONG TIN CHUYEN XE\n\n";

    std::string ma = view.getStringInput("Nhap ma chuyen can sua: ");

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

    std::string di = view.getStringInput("Noi di moi: ");
    std::string den = view.getStringInput("Noi den moi: ");

    std::string bien;
    while (true) {
        bien = view.getStringInput("Bien so xe moi: ");
        if (danhSachXe.count(bien)) break;
        view.showError("Bien so [" + bien + "] khong ton tai! Vui long nhap lai.");
    }

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

    std::string taiXe = view.getStringInput("Tai xe moi: ");

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

void QuanLyController::hienThiDanhSachChuyen() {
    view.clearScreen();
    std::cout << "DANH SACH CHUYEN XE\n";
    view.displayDanhSachChuyenXe(danhSachChuyenXe);
    view.pressAnyKey();
}

void QuanLyController::sapXepChuyen() {
    view.clearScreen();
    std::cout << "SAP XEP CHUYEN XE\n";

    // map khong sap xep duoc, chuyen sang vector de sort roi hien thi
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

void QuanLyController::datVe() {
    view.clearScreen();
    std::cout << "DAT VE\n\n";

    std::string maVe;
    while (true) {
        maVe = view.getStringInput("Nhap ma ve: ");
        if (maVe.empty()) {
            view.showError("Ma ve khong duoc de trong!");
            continue;
        }
        bool trung = false;
        for (const auto& ve : danhSachVe) {
            if (ve.getMaVe() == maVe) {
                view.showError("Ma ve [" + maVe + "] da ton tai! Vui long nhap ma khac.");
                trung = true;
                break;
            }
        }
        if (!trung) break;
    }

    std::string maChuyen;
    ChuyenXe* chuyen = nullptr;
    while (true) {
        maChuyen = view.getStringInput("Nhap ma chuyen xe: ");
        auto it = danhSachChuyenXe.find(maChuyen);
        if (it != danhSachChuyenXe.end()) {
            chuyen = it->second;
            break;
        }
        view.showError("Ma chuyen [" + maChuyen + "] khong ton tai! Vui long nhap lai.");
    }

    std::cout << "\nThong tin chuyen xe\n";
    view.displayChuyenXe(chuyen);

    int sucChua = getSucChuaXe(chuyen->getBienSoXe());
    int soVeHienTai = demHanhKhachTheoChuyen(maChuyen);

    if (sucChua > 0 && soVeHienTai >= sucChua) {
        view.showError("Chuyen xe nay da day! (" + std::to_string(soVeHienTai) + "/" + std::to_string(sucChua) + " cho)");
        view.pressAnyKey();
        return;
    }

    if (sucChua > 0) {
        std::cout << "  Con " << (sucChua - soVeHienTai) << "/" << sucChua << " cho trong.\n\n";
    }

    std::string noiDi = view.getStringInput("Nhap noi di: ");
    std::string noiDen = view.getStringInput("Nhap noi den: ");

    std::string cccd;
    while (true) {
        cccd = view.getStringInput("Nhap CCCD hanh khach (12 so): ");
        if (isValidCCCD(cccd)) break;
        view.showError("CCCD phai la 12 chu so! Vui long nhap lai.");
    }

    bool foundHanhKhach = danhSachHanhKhach.count(cccd) > 0;
    if (foundHanhKhach) {
        auto& hk = danhSachHanhKhach.at(cccd);
        std::cout << "  Hanh khach: " << hk.getTen() << " (SDT: " << hk.getSDT() << ")\n";
    }

    if (!foundHanhKhach) {
        std::cout << "\n[INFO] Hanh khach moi! Vui long nhap thong tin:\n";
        std::string ten = view.getStringInput("Nhap ho ten: ");

        std::string sdt;
        while (true) {
            sdt = view.getStringInput("Nhap SDT (10-11 so): ");
            if (isValidSDT(sdt)) break;
            view.showError("SDT phai la 10-11 chu so! Vui long nhap lai.");
        }
        danhSachHanhKhach.emplace(cccd, HanhKhach(cccd, ten, sdt));
    }

    double gia;
    while (true) {
        gia = view.getDoubleInput("Nhap gia tien (VND): ");
        if (gia > 0) break;
        view.showError("Gia tien phai lon hon 0! Vui long nhap lai.");
    }

    std::cout << "\nThong tin ve\n";
    std::cout << "  Ma Ve: " << maVe << " | Chuyen: " << maChuyen
              << " | CCCD: " << cccd << " | Gia: " << std::fixed << std::setprecision(0) << gia << " VND"
              << " | " << noiDi << " -> " << noiDen << "\n";

    if (view.confirmYN("Xac nhan dat ve?")) {
        danhSachVe.emplace_back(maVe, maChuyen, cccd, gia, noiDi, noiDen);
        chuyen->tangHanhKhach();
        view.showMessage("Dat ve thanh cong! So hanh khach chuyen " + maChuyen + ": " + std::to_string(chuyen->getSoHanhKhach()));
    } else {
        if (!foundHanhKhach) {
            danhSachHanhKhach.erase(cccd);
        }
        view.showMessage("Da huy thao tac dat ve.");
    }
    view.pressAnyKey();
}

void QuanLyController::huyVe() {
    view.clearScreen();
    std::cout << "HUY VE\n\n";

    std::string maVe = view.getStringInput("Nhap ma ve can huy: ");

    bool found = false;
    std::string maChuyenLienQuan;
    for (const auto& ve : danhSachVe) {
        if (ve.getMaVe() == maVe) {
            std::cout << "\nThong tin ve se huy\n";
            view.displayVe(ve);
            maChuyenLienQuan = ve.getMaChuyenXe();
            found = true;
            break;
        }
    }

    if (!found) {
        view.showError("Khong tim thay ve voi ma [" + maVe + "]!");
        view.pressAnyKey();
        return;
    }

    if (view.confirmYN("Xac nhan huy ve nay?")) {
        auto it = std::remove_if(danhSachVe.begin(), danhSachVe.end(),
            [&](const Ve& ve) { return ve.getMaVe() == maVe; });
        danhSachVe.erase(it, danhSachVe.end());

        auto itCX = danhSachChuyenXe.find(maChuyenLienQuan);
        if (itCX != danhSachChuyenXe.end()) {
            itCX->second->giamHanhKhach();
            view.showMessage("Huy ve thanh cong! So HK chuyen " + maChuyenLienQuan + ": " + std::to_string(itCX->second->getSoHanhKhach()));
        } else {
            view.showMessage("Huy ve thanh cong!");
        }
    } else {
        view.showMessage("Da huy thao tac.");
    }
    view.pressAnyKey();
}

void QuanLyController::timKiemVe() {
    view.clearScreen();
    std::cout << "TIM KIEM VE\n\n";

    std::string maVe = view.getStringInput("Nhap ma ve can tim: ");
    for (const auto& ve : danhSachVe) {
        if (ve.getMaVe() == maVe) {
            std::cout << "\nKet qua tim kiem\n";
            view.displayVe(ve);
            view.pressAnyKey();
            return;
        }
    }
    view.showError("Khong tim thay ve voi ma [" + maVe + "]!");
    view.pressAnyKey();
}

void QuanLyController::suaThongTinVe() {
    view.clearScreen();
    std::cout << "SUA THONG TIN VE\n\n";

    std::string maVe = view.getStringInput("Nhap ma ve can sua: ");
    for (auto& ve : danhSachVe) {
        if (ve.getMaVe() == maVe) {
            std::cout << "\nThong tin hien tai\n";
            view.displayVe(ve);
            std::cout << "\n";

            std::string maChuyen;
            while (true) {
                maChuyen = view.getStringInput("Ma chuyen xe moi: ");
                if (danhSachChuyenXe.count(maChuyen)) break;
                view.showError("Ma chuyen [" + maChuyen + "] khong ton tai! Vui long nhap lai.");
            }

            std::string cccd;
            while (true) {
                cccd = view.getStringInput("CCCD moi (12 so): ");
                if (isValidCCCD(cccd)) break;
                view.showError("CCCD phai la 12 chu so! Vui long nhap lai.");
            }

            double gia;
            while (true) {
                gia = view.getDoubleInput("Gia tien moi (VND): ");
                if (gia > 0) break;
                view.showError("Gia tien phai lon hon 0! Vui long nhap lai.");
            }

            std::string noiDi = view.getStringInput("Noi di moi: ");
            std::string noiDen = view.getStringInput("Noi den moi: ");

            std::cout << "\nThong tin moi\n";
            std::cout << "  Ma Ve: " << maVe << " | Chuyen: " << maChuyen
                      << " | CCCD: " << cccd << " | Gia: " << std::fixed << std::setprecision(0) << gia << " VND"
                      << " | " << noiDi << " -> " << noiDen << "\n";

            if (view.confirmYN("Xac nhan sua thong tin ve?")) {
                std::string maChuyenCu = ve.getMaChuyenXe();
                if (maChuyenCu != maChuyen) {
                    auto itCu = danhSachChuyenXe.find(maChuyenCu);
                    if (itCu != danhSachChuyenXe.end()) itCu->second->giamHanhKhach();
                }

                ve.setMaChuyenXe(maChuyen);
                ve.setCCCDHanhKhach(cccd);
                ve.setGiaTien(gia);
                ve.setNoiDi(noiDi);
                ve.setNoiDen(noiDen);

                if (maChuyenCu != maChuyen) {
                    auto itMoi = danhSachChuyenXe.find(maChuyen);
                    if (itMoi != danhSachChuyenXe.end()) itMoi->second->tangHanhKhach();
                }

                view.showMessage("Sua thong tin ve thanh cong!");
            } else {
                view.showMessage("Da huy thao tac sua.");
            }
            view.pressAnyKey();
            return;
        }
    }
    view.showError("Khong tim thay ve voi ma [" + maVe + "]!");
    view.pressAnyKey();
}

void QuanLyController::hienThiDanhSachVe() {
    view.clearScreen();
    std::cout << "DANH SACH VE\n";
    view.displayDanhSachVe(danhSachVe);
    view.pressAnyKey();
}

void QuanLyController::thongKeTongQuat() {
    view.clearScreen();
    std::cout << "THONG KE TONG QUAT\n\n";

    double tongDoanhThu = 0;
    int tongHK = 0;
    for (const auto& entry : danhSachChuyenXe) {
        const auto* cx = entry.second;
        tongDoanhThu += cx->tinhDoanhThu();
        tongHK += cx->getSoHanhKhach();
    }

    std::cout << "+------------------------------------+------------------+\n";
    std::cout << "|            Chi tieu                |     Gia tri      |\n";
    std::cout << "+------------------------------------+------------------+\n";
    std::cout << "| Tong so xe                         | " << std::setw(16) << std::right << danhSachXe.size() << " |\n";
    std::cout << "| Tong so hanh khach (dang ky)       | " << std::setw(16) << std::right << danhSachHanhKhach.size() << " |\n";
    std::cout << "| Tong so ve da dat                  | " << std::setw(16) << std::right << danhSachVe.size() << " |\n";
    std::cout << "| Tong so chuyen xe                  | " << std::setw(16) << std::right << danhSachChuyenXe.size() << " |\n";
    std::cout << "| Tong hanh khach tren cac chuyen    | " << std::setw(16) << std::right << tongHK << " |\n";
    std::cout << "| Tong doanh thu (VND)               | " << std::setw(16) << std::right << std::fixed << std::setprecision(0) << tongDoanhThu << " |\n";
    std::cout << "+------------------------------------+------------------+\n";

    if (!danhSachChuyenXe.empty()) {
        std::cout << "\nChi tiet hanh khach theo chuyen\n";
        std::cout << "+--------+----------------+----------------+-------+------+----------+\n";
        std::cout << "| Ma     |    Noi Di      |    Noi Den     |  Gio  |  HK  | Suc Chua |\n";
        std::cout << "+--------+----------------+----------------+-------+------+----------+\n";
        for (const auto& entry : danhSachChuyenXe) {
            const auto* cx = entry.second;
            int sc = getSucChuaXe(cx->getBienSoXe());
            std::string scStr = (sc >= 0) ? std::to_string(sc) : "N/A";
            std::cout << "| " << std::setw(6) << std::left << cx->getMaChuyen() << " "
                      << "| " << std::setw(14) << std::left << cx->getNoiDi() << " "
                      << "| " << std::setw(14) << std::left << cx->getNoiDen() << " "
                      << "| " << std::setw(5) << std::left << cx->getGioKhoiHanh() << " "
                      << "| " << std::setw(4) << std::right << cx->getSoHanhKhach() << " "
                      << "| " << std::setw(8) << std::right << scStr << " |\n";
        }
        std::cout << "+--------+----------------+----------------+-------+------+----------+\n";
    }

    view.pressAnyKey();
}

void QuanLyController::xemLichTrinhTrongNgay() {
    view.clearScreen();
    std::cout << "LICH TRINH TRONG NGAY\n\n";

    std::string ngay = view.getStringInput("Nhap ngay can xem (DD/MM/YYYY): ");

    std::vector<ChuyenXe*> filtered;
    for (const auto& entry : danhSachChuyenXe) {
        auto* cx = entry.second;
        if (cx->getNgayKhoiHanh() == ngay) {
            filtered.push_back(cx);
        }
    }

    if (filtered.empty()) {
        view.showMessage("Khong co lich trinh nao trong ngay " + ngay + ".");
    } else {
        // sort theo time
        std::sort(filtered.begin(), filtered.end(), [](ChuyenXe* a, ChuyenXe* b) {
            return a->getGioKhoiHanh() < b->getGioKhoiHanh();
        });
        std::cout << "\nLich trinh ngay " << ngay << ":\n";
        view.displayDanhSachChuyenXe(filtered);
    }
    view.pressAnyKey();
}

void QuanLyController::traCuuTaiXe() {
    view.clearScreen();
    std::cout << "TRA CUU TAI XE\n\n";

    std::string tenTX = view.getStringInput("Nhap ten tai xe: ");

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

void QuanLyController::traCuuKhachHang() {
    view.clearScreen();
    std::cout << "TRA CUU KHACH HANG\n\n";

    std::string query = view.getStringInput("Nhap ten hoac CCCD khach hang: ");
    bool found = false;

    for (const auto& entry : danhSachHanhKhach) {
        const auto& hk = entry.second;
        if (hk.getTen() == query || hk.getCCCD() == query) {
            std::cout << "\nThong tin khach hang\n";
            view.displayHanhKhach(hk);

            std::vector<Ve> veOfHK;
            for (const auto& ve : danhSachVe) {
                if (ve.getCCCDHanhKhach() == hk.getCCCD()) {
                    veOfHK.push_back(ve);
                }
            }

            if (veOfHK.empty()) {
                std::cout << "  Khach hang chua dat ve nao.\n";
            } else {
                std::cout << "\nVe da dat\n";
                view.displayDanhSachVe(veOfHK);
            }
            found = true;
        }
    }
    if (!found) view.showError("Khong tim thay khach hang [" + query + "]!");
    view.pressAnyKey();
}
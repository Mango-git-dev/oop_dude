#include "QuanLyController.h"
#include "../exception/CustomException.h"
#include "../model/ChuyenXeThuong.h"
#include "../model/ChuyenXeVIP.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <iomanip>

// --- Helper Functions ---
static std::vector<std::string> splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

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

// --- Constructor & Destructor ---
QuanLyController::QuanLyController() {
    try {
        loadData();
    } catch (const std::exception& e) {
        view.showError(e.what());
    }
}

QuanLyController::~QuanLyController() {
    saveData();
    for (auto* cx : danhSachChuyenXe) {
        delete cx;
    }
}

// --- File I/O ---
void QuanLyController::loadData() {
    // Load Xe
    std::ifstream fileXe("data/xe.csv");
    if (fileXe.is_open()) {
        std::string line;
        while (std::getline(fileXe, line)) {
            auto tokens = splitString(line, ',');
            if (tokens.size() >= 3) {
                danhSachXe.emplace_back(tokens[0], tokens[1], std::stoi(tokens[2]));
            }
        }
        fileXe.close();
    }

    // Load Hanh Khach
    std::ifstream fileHK("data/hanh_khach.csv");
    if (fileHK.is_open()) {
        std::string line;
        while (std::getline(fileHK, line)) {
            auto tokens = splitString(line, ',');
            if (tokens.size() >= 3) {
                danhSachHanhKhach.emplace_back(tokens[0], tokens[1], tokens[2]);
            }
        }
        fileHK.close();
    }

    // Load Ve
    std::ifstream fileVe("data/ve.csv");
    if (fileVe.is_open()) {
        std::string line;
        while (std::getline(fileVe, line)) {
            auto tokens = splitString(line, ',');
            if (tokens.size() >= 4) {
                danhSachVe.emplace_back(tokens[0], tokens[1], tokens[2], std::stod(tokens[3]));
            }
        }
        fileVe.close();
    }

    // Load Chuyen Xe
    std::ifstream fileCX("data/chuyen_xe.csv");
    if (fileCX.is_open()) {
        std::string line;
        while (std::getline(fileCX, line)) {
            auto tokens = splitString(line, ',');
            if (tokens.size() >= 8) {
                int type = std::stoi(tokens[0]);
                std::string ma = tokens[1];
                std::string di = tokens[2];
                std::string den = tokens[3];
                std::string bien = tokens[4];
                double kc = std::stod(tokens[5]);
                std::string ngay = tokens[6];
                std::string taiXe = tokens[7];
                
                if (type == 1) {
                    danhSachChuyenXe.push_back(new ChuyenXeThuong(ma, di, den, bien, kc, ngay, taiXe));
                } else if (type == 2 && tokens.size() >= 9) {
                    double phi = std::stod(tokens[8]);
                    danhSachChuyenXe.push_back(new ChuyenXeVIP(ma, di, den, bien, kc, ngay, taiXe, phi));
                }
            }
        }
        fileCX.close();
    }
}

void QuanLyController::saveData() const {
    std::ofstream fileXe("data/xe.csv");
    if (!fileXe) throw FileException("Cannot open data/xe.csv for writing");
    for (const auto& xe : danhSachXe) {
        fileXe << xe.toCSV() << "\n";
    }

    std::ofstream fileHK("data/hanh_khach.csv");
    for (const auto& hk : danhSachHanhKhach) {
        fileHK << hk.toCSV() << "\n";
    }

    std::ofstream fileVe("data/ve.csv");
    for (const auto& ve : danhSachVe) {
        fileVe << ve.toCSV() << "\n";
    }

    std::ofstream fileCX("data/chuyen_xe.csv");
    for (const auto* cx : danhSachChuyenXe) {
        fileCX << cx->toCSV() << "\n";
    }
}

// --- Main Loop ---
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
            }
            saveData(); // Auto save after every action
        } catch (const std::exception& e) {
            view.showError(e.what());
        }
    }
}

// --- QUAN LY XE ---
void QuanLyController::themXe() {
    std::string bienSo = view.getStringInput("Nhap bien so xe: ");
    std::string loai = view.getStringInput("Nhap loai xe: ");
    int ghe = view.getIntInput("Nhap so ghe: ");
    if (ghe <= 0) throw InvalidDataException("So ghe phai lon hon 0");
    danhSachXe.emplace_back(bienSo, loai, ghe);
    view.showMessage("Them xe thanh cong!");
}

void QuanLyController::xoaXe() {
    std::string bienSo = view.getStringInput("Nhap bien so can xoa: ");
    auto it = std::remove_if(danhSachXe.begin(), danhSachXe.end(), 
        [&](const Xe& xe) { return xe.getBienSo() == bienSo; });
    
    if (it != danhSachXe.end()) {
        danhSachXe.erase(it, danhSachXe.end());
        view.showMessage("Xoa xe thanh cong!");
    } else {
        view.showError("Khong tim thay xe!");
    }
}

void QuanLyController::timKiemXe() {
    std::string bienSo = view.getStringInput("Nhap bien so can tim: ");
    for (const auto& xe : danhSachXe) {
        if (xe.getBienSo() == bienSo) {
            view.displayXe(xe);
            return;
        }
    }
    view.showError("Khong tim thay xe!");
}

void QuanLyController::suaThongTinXe() {
    std::string bienSo = view.getStringInput("Nhap bien so can sua: ");
    for (auto& xe : danhSachXe) {
        if (xe.getBienSo() == bienSo) {
            std::string loai = view.getStringInput("Nhap loai xe moi: ");
            int ghe = view.getIntInput("Nhap so ghe moi: ");
            if (ghe <= 0) throw InvalidDataException("So ghe phai lon hon 0");
            xe.setLoaiXe(loai);
            xe.setSoGhe(ghe);
            view.showMessage("Sua thong tin thanh cong!");
            return;
        }
    }
    view.showError("Khong tim thay xe!");
}

void QuanLyController::hienThiToanBoXe() {
    for (const auto& xe : danhSachXe) {
        view.displayXe(xe);
    }
}

// --- QUAN LY CHUYEN ---
void QuanLyController::themChuyen() {
    int loai = view.getIntInput("Nhap loai chuyen (1-Thuong, 2-VIP): ");
    std::string ma = view.getStringInput("Ma chuyen: ");
    std::string di = view.getStringInput("Noi di: ");
    std::string den = view.getStringInput("Noi den: ");
    std::string bien = view.getStringInput("Bien so xe: ");
    double kc = view.getDoubleInput("Khoang cach (km): ");
    if (kc <= 0) throw InvalidDataException("Khoang cach phai lon hon 0");
    std::string ngay = view.getStringInput("Ngay khoi hanh (DD/MM/YYYY): ");
    std::string taiXe = view.getStringInput("Ten tai xe: ");

    if (loai == 1) {
        danhSachChuyenXe.push_back(new ChuyenXeThuong(ma, di, den, bien, kc, ngay, taiXe));
        view.showMessage("Them chuyen xe thuong thanh cong!");
    } else if (loai == 2) {
        double phuPhi = view.getDoubleInput("Phu phi dich vu VIP: ");
        if (phuPhi < 0) throw InvalidDataException("Phu phi khong the am");
        danhSachChuyenXe.push_back(new ChuyenXeVIP(ma, di, den, bien, kc, ngay, taiXe, phuPhi));
        view.showMessage("Them chuyen xe VIP thanh cong!");
    } else {
        view.showError("Loai chuyen khong hop le!");
    }
}

void QuanLyController::huyChuyen() {
    std::string ma = view.getStringInput("Nhap ma chuyen can huy: ");
    auto it = std::remove_if(danhSachChuyenXe.begin(), danhSachChuyenXe.end(), 
        [&](ChuyenXe* cx) {
            if (cx->getMaChuyen() == ma) {
                delete cx;
                return true;
            }
            return false;
        });
    
    if (it != danhSachChuyenXe.end()) {
        danhSachChuyenXe.erase(it, danhSachChuyenXe.end());
        view.showMessage("Huy chuyen thanh cong!");
    } else {
        view.showError("Khong tim thay chuyen xe!");
    }
}

void QuanLyController::timKiemChuyen() {
    std::string ma = view.getStringInput("Nhap ma chuyen can tim: ");
    for (const auto* cx : danhSachChuyenXe) {
        if (cx->getMaChuyen() == ma) {
            view.displayChuyenXe(cx);
            return;
        }
    }
    view.showError("Khong tim thay chuyen xe!");
}

void QuanLyController::suaThongTinChuyen() {
    std::string ma = view.getStringInput("Nhap ma chuyen can sua: ");
    for (auto* cx : danhSachChuyenXe) {
        if (cx->getMaChuyen() == ma) {
            std::string di = view.getStringInput("Noi di moi: ");
            std::string den = view.getStringInput("Noi den moi: ");
            std::string bien = view.getStringInput("Bien so xe moi: ");
            double kc = view.getDoubleInput("Khoang cach moi (km): ");
            if (kc <= 0) throw InvalidDataException("Khoang cach phai lon hon 0");
            std::string ngay = view.getStringInput("Ngay khoi hanh moi: ");
            std::string taiXe = view.getStringInput("Tai xe moi: ");
            
            cx->setNoiDi(di);
            cx->setNoiDen(den);
            cx->setBienSoXe(bien);
            cx->setKhoangCach(kc);
            cx->setNgayKhoiHanh(ngay);
            cx->setTenTaiXe(taiXe);
            view.showMessage("Sua thong tin thanh cong!");
            return;
        }
    }
    view.showError("Khong tim thay chuyen xe!");
}

void QuanLyController::hienThiDanhSachChuyen() {
    for (const auto* cx : danhSachChuyenXe) {
        view.displayChuyenXe(cx);
    }
}

void QuanLyController::sapXepChuyen() {
    std::sort(danhSachChuyenXe.begin(), danhSachChuyenXe.end(), [](ChuyenXe* a, ChuyenXe* b) {
        return a->getKhoangCach() < b->getKhoangCach(); // Sort by distance ascending
    });
    view.showMessage("Da sap xep chuyen xe theo khoang cach tang dan!");
    hienThiDanhSachChuyen();
}

// --- QUAN LY VE ---
void QuanLyController::datVe() {
    std::string maVe = view.getStringInput("Nhap ma ve: ");
    std::string maChuyen = view.getStringInput("Nhap ma chuyen xe: ");
    std::string cccd = view.getStringInput("Nhap CCCD hanh khach (12 so): ");
    if (!isValidCCCD(cccd)) throw InvalidDataException("CCCD phai la 12 so hop le");
    double gia = view.getDoubleInput("Nhap gia tien: ");
    if (gia <= 0) throw InvalidDataException("Gia tien phai lon hon 0");
    
    // Auto create HanhKhach if not exists (Simplified logic)
    bool foundHanhKhach = false;
    for (const auto& hk : danhSachHanhKhach) {
        if (hk.getCCCD() == cccd) foundHanhKhach = true;
    }
    if (!foundHanhKhach) {
        std::string ten = view.getStringInput("Hanh khach moi! Nhap ten: ");
        std::string sdt = view.getStringInput("Nhap SDT (10-11 so): ");
        if (!isValidSDT(sdt)) throw InvalidDataException("SDT phai la 10-11 so hop le");
        danhSachHanhKhach.emplace_back(cccd, ten, sdt);
    }
    
    danhSachVe.emplace_back(maVe, maChuyen, cccd, gia);
    view.showMessage("Dat ve thanh cong!");
}

void QuanLyController::huyVe() {
    std::string maVe = view.getStringInput("Nhap ma ve can huy: ");
    auto it = std::remove_if(danhSachVe.begin(), danhSachVe.end(), 
        [&](const Ve& ve) { return ve.getMaVe() == maVe; });
    
    if (it != danhSachVe.end()) {
        danhSachVe.erase(it, danhSachVe.end());
        view.showMessage("Huy ve thanh cong!");
    } else {
        view.showError("Khong tim thay ve!");
    }
}

void QuanLyController::timKiemVe() {
    std::string maVe = view.getStringInput("Nhap ma ve can tim: ");
    for (const auto& ve : danhSachVe) {
        if (ve.getMaVe() == maVe) {
            view.displayVe(ve);
            return;
        }
    }
    view.showError("Khong tim thay ve!");
}

void QuanLyController::suaThongTinVe() {
    std::string maVe = view.getStringInput("Nhap ma ve can sua: ");
    for (auto& ve : danhSachVe) {
        if (ve.getMaVe() == maVe) {
            std::string maChuyen = view.getStringInput("Ma chuyen xe moi: ");
            std::string cccd = view.getStringInput("CCCD moi (12 so): ");
            if (!isValidCCCD(cccd)) throw InvalidDataException("CCCD phai la 12 so hop le");
            double gia = view.getDoubleInput("Gia tien moi: ");
            if (gia <= 0) throw InvalidDataException("Gia tien phai lon hon 0");
            
            ve.setMaChuyenXe(maChuyen);
            ve.setCCCDHanhKhach(cccd);
            ve.setGiaTien(gia);
            view.showMessage("Sua thong tin thanh cong!");
            return;
        }
    }
    view.showError("Khong tim thay ve!");
}

void QuanLyController::hienThiDanhSachVe() {
    for (const auto& ve : danhSachVe) {
        view.displayVe(ve);
    }
}

// --- TONG QUAN ---
void QuanLyController::thongKeTongQuat() {
    double tongDoanhThu = 0;
    for (const auto* cx : danhSachChuyenXe) {
        tongDoanhThu += cx->tinhDoanhThu();
    }
    std::cout << "[THONG KE] Tong doanh thu tat ca cac chuyen xe: " << std::fixed << std::setprecision(0) << tongDoanhThu << " VND\n";
    std::cout << "[THONG KE] Tong so xe: " << danhSachXe.size() << "\n";
    std::cout << "[THONG KE] Tong so hanh khach: " << danhSachHanhKhach.size() << "\n";
    std::cout << "[THONG KE] Tong so ve: " << danhSachVe.size() << "\n";
}

void QuanLyController::xemLichTrinhTrongNgay() {
    std::string ngay = view.getStringInput("Nhap ngay can xem (DD/MM/YYYY): ");
    bool found = false;
    for (const auto* cx : danhSachChuyenXe) {
        if (cx->getNgayKhoiHanh() == ngay) {
            view.displayChuyenXe(cx);
            found = true;
        }
    }
    if (!found) view.showMessage("Khong co lich trinh nao trong ngay nay.");
}

void QuanLyController::traCuuTaiXe() {
    std::string tenTX = view.getStringInput("Nhap ten tai xe: ");
    bool found = false;
    for (const auto* cx : danhSachChuyenXe) {
        if (cx->getTenTaiXe() == tenTX) {
            view.displayChuyenXe(cx);
            found = true;
        }
    }
    if (!found) view.showError("Khong tim thay tai xe hoac tai xe chua co chuyen!");
}

void QuanLyController::traCuuKhachHang() {
    std::string query = view.getStringInput("Nhap ten hoac CCCD khach hang: ");
    bool found = false;
    for (const auto& hk : danhSachHanhKhach) {
        if (hk.getTen() == query || hk.getCCCD() == query) {
            view.displayHanhKhach(hk);
            
            // Hien thi them ve cua khach hang nay
            std::cout << "--- Ve da dat ---\n";
            for (const auto& ve : danhSachVe) {
                if (ve.getCCCDHanhKhach() == hk.getCCCD()) {
                    view.displayVe(ve);
                }
            }
            found = true;
        }
    }
    if (!found) view.showError("Khong tim thay khach hang!");
}

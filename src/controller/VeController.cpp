#include "VeController.h"
#include "StringUtil.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <climits>

static bool isValidSDT(const std::string& sdt) {
    if (sdt.length() != 10 && sdt.length() != 11) return false;
    for (char c : sdt) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

static bool isValidCCCD(const std::string& cccd) {
    if (cccd.length() != 12) return false;
    for (char c : cccd) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

// yyyy-mm-dd, hh:mm
static long long parseToMinutes(const std::string& ngay, const std::string& gio) {
    if (ngay.size() < 10 || gio.size() < 5) return -1;
    try {
        int yyyy = std::stoi(ngay.substr(0, 4));
        int mm   = std::stoi(ngay.substr(5, 2));
        int dd   = std::stoi(ngay.substr(8, 2));
        int hh   = std::stoi(gio.substr(0, 2));
        int mi   = std::stoi(gio.substr(3, 2));
        
        //so sanh tuong doi khong tinh nam nhuan
        long long totalDays = (long long)yyyy * 365 + mm * 31 + dd;
        return totalDays * 24 * 60 + hh * 60 + mi;
    } catch (...) {
        return -1;
    }
}

// tinh nam nhuan 
static int soNgayTrongThangVe(int thang, int nam) {
    if (thang == 2) return (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0)) ? 29 : 28;
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11) return 30;
    return 31;
}

static long long nhapThoiGianVe(const std::string& label, const ConsoleView& view) {
    std::cout << "\n[" << label << "]\n";

    int nam = 0;
    while (true) {
        try {
            nam = view.getIntInput("  Nam : ");
            if (nam >= 0 && nam <= 9999) break;
            view.showError("Nam khong hop le! Vui long nhap tu 0 den 9999.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    int thang = 0;
    while (true) {
        try {
            thang = view.getIntInput("  Thang : ");
            if (thang >= 1 && thang <= 12) break;
            view.showError("Thang khong hop le! Vui long nhap tu 1 den 12.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    int maxNgay = soNgayTrongThangVe(thang, nam);
    int ngay = 0;
    while (true) {
        try {
            ngay = view.getIntInput("  Ngay (1-" + std::to_string(maxNgay) + ")   : ");
            if (ngay >= 1 && ngay <= maxNgay) break;
            view.showError("Ngay khong hop le! Thang " + std::to_string(thang) + "/" + std::to_string(nam) +
                           " chi co " + std::to_string(maxNgay) + " ngay.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    int gio = 0;
    while (true) {
        try {
            gio = view.getIntInput("  Gio : ");
            if (gio >= 0 && gio <= 23) break;
            view.showError("Gio khong hop le! Vui long nhap tu 0 den 23.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    int phut = 0;
    while (true) {
        try {
            phut = view.getIntInput("  Phut : ");
            if (phut >= 0 && phut <= 59) break;
            view.showError("Phut khong hop le! Vui long nhap tu 0 den 59.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(4) << nam << "-"
        << std::setw(2) << thang << "-"
        << std::setw(2) << ngay;
    std::string ngayStr = oss.str();

    std::ostringstream ossGio;
    ossGio << std::setfill('0') << std::setw(2) << gio << ":" << std::setw(2) << phut;
    std::string gioStr = ossGio.str();

    std::cout << "  => Da chon: " << ngayStr << " " << gioStr << "\n";
    return parseToMinutes(ngayStr, gioStr);
}

// lay danh sach co san(con cho trong)
static void layChuyenCoSan(const std::map<std::string, ChuyenXe*>& danhSachChuyenXe,
                            const std::vector<Ve>& danhSachVe,
                            const XeController& xeController,
                            std::vector<ChuyenXe*>& availableTrips,
                            std::vector<int>& choTrongList) {
    for (const auto& entry : danhSachChuyenXe) {
        auto* cx = entry.second;
        int sucChua = xeController.getSucChuaXe(cx->getBienSoXe());
        int countVe = 0;
        for (const auto& ve : danhSachVe) {
            if (ve.getMaChuyenXe() == cx->getMaChuyen()) countVe++;
        }
        int choTrong = (sucChua > 0) ? (sucChua - countVe) : 99;
        if (sucChua <= 0 || choTrong > 0) {
            availableTrips.push_back(cx);
            choTrongList.push_back(choTrong);
        }
    }
}

VeController::VeController(std::vector<Ve>& dsVe, std::map<std::string, HanhKhach>& dsHK, std::map<std::string, ChuyenXe*>& dsChuyen, const XeController& xeCtrl, const ConsoleView& consoleView)
    : danhSachVe(dsVe), danhSachHanhKhach(dsHK), danhSachChuyenXe(dsChuyen), xeController(xeCtrl), view(consoleView) {}

std::string VeController::generateMaVe() const {
    int maxId = 0;
    for (const auto& ve : danhSachVe) {
        std::string ma = ve.getMaVe();
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
    ss << "VE" << std::setw(2) << std::setfill('0') << nextId;
    return ss.str();
}

int VeController::chonIndexVe(const std::string& promptMsg) const {
    if (danhSachVe.empty()) {
        view.showMessage("Danh sach ve trong.");
        return -1;
    }
    view.displayDanhSachVe(danhSachVe);

    while (true) {
        std::string input = view.getStringInput(promptMsg + " (nhap STT 1-" + std::to_string(danhSachVe.size()) + ", hoac 0 de huy): ");
        if (input == "0") return -1;
        if (input.empty()) continue;

        bool isNum = true;
        for (char c : input) {
            if (!std::isdigit(static_cast<unsigned char>(c))) { isNum = false; break; }
        }
        if (isNum) {
            int stt = std::stoi(input);
            if (stt >= 1 && stt <= (int)danhSachVe.size()) {
                return stt - 1;
            }
        }
        for (size_t i = 0; i < danhSachVe.size(); ++i) {
            if (danhSachVe[i].getMaVe() == input || danhSachVe[i].getCCCDHanhKhach() == input) {
                return (int)i;
            }
        }
        view.showError("Lua chon hoac ma ve khong hop le! (Nhap 0 de huy)");
    }
}

void VeController::datVeKhachHang() {
    view.clearScreen();
    std::cout << "================ DAT VE XE BUS ================\n\n";

    if (danhSachChuyenXe.empty()) {
        view.showError("Hien khong co chuyen xe nao trong he thong!");
        view.pressAnyKey();
        return;
    }

    std::cout << "CHON CHUC NANG TIM CHUYEN XE:\n";
    std::cout << "  1. Xem tat ca chuyen xe co san\n";
    std::cout << "  2. Tim kiem theo noi di, noi den va thoi gian\n";
    std::cout << "  0. Quay lai\n";
    int chucNang = 0;
    while (true) {
        try {
            chucNang = view.getIntInput("Nhap lua chon (0-2): ");
            if (chucNang >= 0 && chucNang <= 2) break;
            view.showError("Vui long nhap 0, 1 hoac 2!");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }
    if (chucNang == 0) return;

    std::vector<ChuyenXe*> availableTrips;
    std::vector<int> choTrongList;

    // IDK man
    std::vector<ChuyenXe*> tatCaChuyen;
    std::vector<int> tatCaChoTrong;
    layChuyenCoSan(danhSachChuyenXe, danhSachVe, xeController, tatCaChuyen, tatCaChoTrong);

    if (tatCaChuyen.empty()) {
        view.showError("Tat ca cac chuyen xe hien tai deu da day cho!");
        view.pressAnyKey();
        return;
    }

    if (chucNang == 1) {
        availableTrips = tatCaChuyen;
        choTrongList   = tatCaChoTrong;
    } else {
        std::cout << "\n--- TIM KIEM CHUYEN XE ---\n";
        std::string noiDi;
        while (true) {
            noiDi = StringUtil::normalizeName(view.getStringInput("Nhap noi di  : "));
            if (!noiDi.empty()) break;
            view.showError("Vui long nhap noi di!");
        }
        std::string noiDen;
        while (true) {
            noiDen = StringUtil::normalizeName(view.getStringInput("Nhap noi den : "));
            if (!noiDen.empty()) break;
            view.showError("Vui long nhap noi den!");
        }

        long long tuPhut  = nhapThoiGianVe("Thoi gian BAT DAU ", view);
        long long denPhut = nhapThoiGianVe("Thoi gian KET THUC ", view);

        if (tuPhut < 0 || denPhut < 0 || tuPhut > denPhut) {
            view.showError("Khoang thoi gian khong hop le! Thoi gian bat dau phai truoc thoi gian ket thuc.");
            view.pressAnyKey();
            return;
        }
        const long long NAM_TIENG = 5 * 60; // 300 phut

        std::vector<ChuyenXe*> ketQua;
        std::vector<int>       ketQuaCho;
        for (size_t i = 0; i < tatCaChuyen.size(); ++i) {
            ChuyenXe* cx = tatCaChuyen[i];
            if (StringUtil::normalizeName(cx->getNoiDi())  != noiDi)  continue;
            if (StringUtil::normalizeName(cx->getNoiDen()) != noiDen) continue;
            long long phutChuyen = parseToMinutes(cx->getNgayKhoiHanh(), cx->getGioKhoiHanh());
            if (phutChuyen < 0) continue;
            if (phutChuyen >= tuPhut && phutChuyen <= denPhut) {
                ketQua.push_back(cx);
                ketQuaCho.push_back(tatCaChoTrong[i]);
            }
        }

        if (ketQua.empty()) {
            long long minKhoangCach = LLONG_MAX;
            ChuyenXe* ganNhat = nullptr;
            int ganNhatCho = 0;
            for (size_t i = 0; i < tatCaChuyen.size(); ++i) {
                ChuyenXe* cx = tatCaChuyen[i];
                if (StringUtil::normalizeName(cx->getNoiDi())  != noiDi)  continue;
                if (StringUtil::normalizeName(cx->getNoiDen()) != noiDen) continue;
                long long phutChuyen = parseToMinutes(cx->getNgayKhoiHanh(), cx->getGioKhoiHanh());
                if (phutChuyen < 0) continue;
                
                long long kc = 0;
                if (phutChuyen < tuPhut)  kc = tuPhut  - phutChuyen;
                else                       kc = phutChuyen - denPhut;
                if (kc < minKhoangCach) {
                    minKhoangCach = kc;
                    ganNhat = cx;
                    ganNhatCho = tatCaChoTrong[i];
                }
            }

            if (ganNhat == nullptr || minKhoangCach > NAM_TIENG) {
                view.showError("Khong tim thay chuyen xe phu hop! (Khong co chuyen nao " + noiDi + " -> " + noiDen + " trong khoang thoi gian hoac gan hon 5 tieng)");
                view.pressAnyKey();
                return;
            } else {
                std::cout << "\n[INFO] Khong co chuyen trong khoang thoi gian da chon.\n";
                std::cout << "[INFO] Chuyen gan nhat tim duoc (cach " << (minKhoangCach / 60) << " gio " << (minKhoangCach % 60) << " phut):\n";
                ketQua.push_back(ganNhat);
                ketQuaCho.push_back(ganNhatCho);
            }
        }

        availableTrips = ketQua;
        choTrongList   = ketQuaCho;
    }

    std::cout << "\nDANH SACH CAC CHUYEN XE DANG CO SAN:\n";
    view.displayDanhSachChuyenXeChoKhach(availableTrips, choTrongList);

    ChuyenXe* chuyenChon = nullptr;
    while (true) {
        try {
            int stt = view.getIntInput("\nChon chuyen xe theo STT (1 - " + std::to_string(availableTrips.size()) + ", hoac 0 de quay lai): ");
            if (stt == 0) return;
            if (stt >= 1 && stt <= (int)availableTrips.size()) {
                chuyenChon = availableTrips[stt - 1];
                break;
            }
            view.showError("STT khong hop le! Vui long nhap lai (hoac 0 de quay lai).");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    if (!chuyenChon) return;

    std::cout << "\n[BAN DA CHON TUYEN XE: " << chuyenChon->getNoiDi() << " -> " << chuyenChon->getNoiDen() << " (" << chuyenChon->getGioKhoiHanh() << " " << chuyenChon->getNgayKhoiHanh() << ")]\n\n";

    std::string cccd;
    while (true) {
        cccd = view.getStringInput("Nhap CCCD hanh khach (12 so, hoac '0' de huy): ");
        if (cccd == "0") return;
        if (isValidCCCD(cccd)) break;
        view.showError("CCCD phai la 12 chu so! Vui long nhap lai.");
    }

    bool foundHanhKhach = danhSachHanhKhach.count(cccd) > 0;
    if (foundHanhKhach) {
        auto& hk = danhSachHanhKhach.at(cccd);
        std::cout << "  Hanh khach ton tai: " << hk.getTen() << " (SDT: " << hk.getSDT() << ")\n";
    } else {
        std::cout << "\n[INFO] Hanh khach moi! Vui long nhap thong tin:\n";
        std::string ten = StringUtil::normalizeName(view.getStringInput("Nhap ho ten hanh khach: "));

        std::string sdt;
        while (true) {
            sdt = view.getStringInput("Nhap SDT (10-11 so): ");
            if (isValidSDT(sdt)) break;
            view.showError("SDT phai la 10-11 chu so! Vui long nhap lai.");
        }
        danhSachHanhKhach.emplace(cccd, HanhKhach(cccd, ten, sdt));
    }

    double gia = chuyenChon->tinhDoanhThu();
    std::string loaiVeStr = (chuyenChon->getType() == 1) ? "Chuyen xe Thuong" : "Chuyen xe VIP";

    std::string maVe = generateMaVe();

    std::cout << "\nTHONG TIN XAC NHAN DAT VE\n";
    std::cout << "  Ma Ve (Tu dong): " << maVe << "\n";
    std::cout << "  Tuyen duong:     " << chuyenChon->getNoiDi() << " -> " << chuyenChon->getNoiDen() << "\n";
    std::cout << "  Hanh khach CCCD: " << cccd << "\n";
    std::cout << "  Loai chuyen xe:  " << loaiVeStr << "\n";
    std::cout << "  Gia ve:          " << StringUtil::formatCurrency(gia) << " VND\n";

    if (view.confirmYN("Ban co muon xac nhan dat ve ?")) {
        danhSachVe.emplace_back(maVe, chuyenChon->getMaChuyen(), cccd, gia, chuyenChon->getNoiDi(), chuyenChon->getNoiDen());
        chuyenChon->tangHanhKhach();
        view.showMessage("Dat ve thanh cong! Ma ve cua ban la: " + maVe);
    } else {
        if (!foundHanhKhach) {
            danhSachHanhKhach.erase(cccd);
        }
        view.showMessage("Da huy thao tac dat ve.");
    }
    view.pressAnyKey();
}

void VeController::traCuuVeKhachHang() {
    view.clearScreen();
    std::cout << "TRA CUU VE XE DA DAT\n\n";

    std::string cccd = StringUtil::trim(view.getStringInput("Nhap so CCCD hanh khach (hoac '0' de huy): "));
    if (cccd == "0" || cccd.empty()) return;

    std::vector<Ve> veOfHK;
    for (const auto& ve : danhSachVe) {
        if (StringUtil::trim(ve.getCCCDHanhKhach()) == cccd) {
            veOfHK.push_back(ve);
        }
    }

    if (veOfHK.empty()) {
        view.showError("Khong tim thay ve xe nao cua hanh khach voi CCCD [" + cccd + "]!");
    } else {
        std::cout << "\nCac ve xe da dat cua hanh khach (CCCD: " << cccd << "):\n";
        view.displayDanhSachVe(veOfHK);
    }
    view.pressAnyKey();
}

void VeController::huyVeKhachHang() {
    view.clearScreen();
    std::cout << "HUY VE XE DA DAT\n\n";

    std::string cccd = StringUtil::trim(view.getStringInput("Nhap so CCCD hanh khach (hoac '0' de huy): "));
    if (cccd == "0" || cccd.empty()) return;

    std::vector<int> userVeIndexes;
    std::vector<Ve> userVeList;
    for (size_t i = 0; i < danhSachVe.size(); ++i) {
        if (StringUtil::trim(danhSachVe[i].getCCCDHanhKhach()) == cccd) {
            userVeIndexes.push_back((int)i);
            userVeList.push_back(danhSachVe[i]);
        }
    }

    if (userVeList.empty()) {
        view.showError("Khong tim thay ve xe nao cua hanh khach voi CCCD [" + cccd + "]!");
        view.pressAnyKey();
        return;
    }

    std::cout << "\nDanh sach ve da dat:\n";
    view.displayDanhSachVe(userVeList);

    int stt = 0;
    while (true) {
        try {
            stt = view.getIntInput("Chon STT ve can huy (1 - " + std::to_string(userVeList.size()) + ", hoac 0 de huy): ");
            if (stt == 0) return;
            if (stt >= 1 && stt <= (int)userVeList.size()) break;
            view.showError("STT khong hop le! Vui long nhap lai.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    int realIdx = userVeIndexes[stt - 1];
    const auto& veHuy = danhSachVe[realIdx];
    std::string maChuyen = veHuy.getMaChuyenXe();

    if (view.confirmYN("Xac nhan huy ve [" + veHuy.getMaVe() + "]?")) {
        danhSachVe.erase(danhSachVe.begin() + realIdx);
        auto itCX = danhSachChuyenXe.find(maChuyen);
        if (itCX != danhSachChuyenXe.end()) {
            itCX->second->giamHanhKhach();
        }
        view.showMessage("Huy ve thanh cong!");
    } else {
        view.showMessage("Da huy thao tac.");
    }
    view.pressAnyKey();
}

void VeController::huyVeQuanLy() {
    view.clearScreen();
    std::cout << "HUY VE (QUAN LY)\n\n";

    int idx = chonIndexVe("Chon ve can huy");
    if (idx < 0 || idx >= (int)danhSachVe.size()) return;

    const auto& ve = danhSachVe[idx];
    std::string maVe = ve.getMaVe();
    std::string maChuyenLienQuan = ve.getMaChuyenXe();

    std::cout << "\nThong tin ve se huy\n";
    view.displayVe(ve);

    if (view.confirmYN("Xac nhan huy ve nay?")) {
        danhSachVe.erase(danhSachVe.begin() + idx);

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

void VeController::timKiemVe() {
    view.clearScreen();
    std::cout << "TIM KIEM VE\n\n";

    int idx = chonIndexVe("Nhap hoac chon ve can tim");
    if (idx >= 0 && idx < (int)danhSachVe.size()) {
        std::cout << "\nKet qua tim kiem\n";
        view.displayVe(danhSachVe[idx]);
    }
    view.pressAnyKey();
}

void VeController::suaThongTinVe() {
    view.clearScreen();
    std::cout << "SUA THONG TIN VE\n\n";

    int idx = chonIndexVe("Chon ve can sua");
    if (idx < 0 || idx >= (int)danhSachVe.size()) return;

    auto& ve = danhSachVe[idx];
    std::cout << "\nThong tin hien tai\n";
    view.displayVe(ve);
    std::cout << "\n";

    std::string maChuyen = view.getStringInput("Nhap ma chuyen xe moi: ");
    if (maChuyen.empty()) return;

    std::string cccd;
    while (true) {
        cccd = view.getStringInput("CCCD moi (12 so): ");
        if (isValidCCCD(cccd)) break;
        view.showError("CCCD phai la 12 chu so! Vui long nhap lai.");
    }

    double gia;
    while (true) {
        try {
            gia = view.getDoubleInput("Gia tien moi (VND): ");
            if (gia > 0) break;
            view.showError("Gia tien phai lon hon 0! Vui long nhap lai.");
        } catch (const std::exception& e) { view.showError(e.what()); }
    }

    std::string noiDi = StringUtil::normalizeName(view.getStringInput("Noi di moi: "));
    std::string noiDen = StringUtil::normalizeName(view.getStringInput("Noi den moi: "));

    std::cout << "\nThong tin ve moi\n";
    std::cout << "  Ma Ve: " << ve.getMaVe() << " | Chuyen: " << maChuyen
              << " | CCCD: " << cccd << " | Gia: " << StringUtil::formatCurrency(gia) << " VND"
              << " | " << noiDi << " -> " << noiDen << "\n";

    if (view.confirmYN("Xac nhan sua thong tin ve?")) {
        std::string maChuyenCu = ve.getMaChuyenXe();

        if (maChuyenCu != maChuyen) {
            auto itCu = danhSachChuyenXe.find(maChuyenCu);
            if (itCu != danhSachChuyenXe.end()) itCu->second->giamHanhKhach();

            auto itMoi = danhSachChuyenXe.find(maChuyen);
            if (itMoi != danhSachChuyenXe.end()) itMoi->second->tangHanhKhach();
        }

        ve.setMaChuyenXe(maChuyen);
        ve.setCCCDHanhKhach(cccd);
        ve.setGiaTien(gia);
        ve.setNoiDi(noiDi);
        ve.setNoiDen(noiDen);

        view.showMessage("Sua thong tin ve thanh cong!");
    } else {
        view.showMessage("Da huy thao tac sua.");
    }
    view.pressAnyKey();
}

void VeController::hienThiDanhSachVe() {
    view.clearScreen();
    std::cout << "DANH SACH TAT CA VE\n";
    view.displayDanhSachVe(danhSachVe);
    view.pressAnyKey();
}

void VeController::traCuuKhachHang() {
    view.clearScreen();
    std::cout << "TRA CUU KHACH HANG\n\n";

    std::string rawInput = view.getStringInput("Nhap ten hoac CCCD khach hang (hoac '0' de huy): ");
    if (rawInput == "0" || rawInput.empty()) return;
    std::string trimmedInput = StringUtil::trim(rawInput);
    std::string normInput = StringUtil::normalizeName(trimmedInput);

    bool found = false;

    for (const auto& entry : danhSachHanhKhach) {
        const auto& hk = entry.second;
        std::string hkCCCD = StringUtil::trim(hk.getCCCD());
        std::string hkTen = StringUtil::trim(hk.getTen());

        if (hkTen == normInput || hkCCCD == trimmedInput) {
            std::cout << "\nThong tin khach hang\n";
            view.displayHanhKhach(hk);

            std::vector<Ve> veOfHK;
            for (const auto& ve : danhSachVe) {
                if (StringUtil::trim(ve.getCCCDHanhKhach()) == hkCCCD) {
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
    if (!found) view.showError("Khong tim thay khach hang [" + trimmedInput + "]!");
    view.pressAnyKey();
}

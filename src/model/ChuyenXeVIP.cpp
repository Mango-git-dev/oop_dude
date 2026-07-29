#include "ChuyenXeVIP.h"
#include <string>

ChuyenXeVIP::ChuyenXeVIP(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string gio, std::string taiXe, double phi, int soHK)
    : ChuyenXe(ma, di, den, bienSo, khoangCach, ngay, gio, taiXe, soHK), phiDichVu(phi) {}

double ChuyenXeVIP::tinhGiaVe() const {
    return (khoangCach * 15000.0) + phiDichVu; // 15,000 VND / km + phu phi
}

int ChuyenXeVIP::getType() const {
    return 2;
}

double ChuyenXeVIP::getPhiDichVu() const {
    return phiDichVu;
}

void ChuyenXeVIP::setPhiDichVu(double phi) {
    phiDichVu = phi;
}

std::string ChuyenXeVIP::toCSV() const {
    return ChuyenXe::toCSV() + "," + std::to_string(phiDichVu);
}

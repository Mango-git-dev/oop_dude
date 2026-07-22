#include "ChuyenXeThuong.h"

ChuyenXeThuong::ChuyenXeThuong(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string taiXe)
    : ChuyenXe(ma, di, den, bienSo, khoangCach, ngay, taiXe) {}

double ChuyenXeThuong::tinhDoanhThu() const {
    return khoangCach * 10000.0; // 10,000 VND / km
}

int ChuyenXeThuong::getType() const {
    return 1;
}

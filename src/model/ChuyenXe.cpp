#include "ChuyenXe.h"
#include <string>

ChuyenXe::ChuyenXe(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string gio, std::string taiXe, int soHK)
    : maChuyen(ma), noiDi(di), noiDen(den), bienSoXe(bienSo), khoangCach(khoangCach), ngayKhoiHanh(ngay), gioKhoiHanh(gio), tenTaiXe(taiXe), soHanhKhach(soHK) {}

std::string ChuyenXe::getMaChuyen() const { return maChuyen; }
std::string ChuyenXe::getNoiDi() const { return noiDi; }
std::string ChuyenXe::getNoiDen() const { return noiDen; }
std::string ChuyenXe::getBienSoXe() const { return bienSoXe; }
double ChuyenXe::getKhoangCach() const { return khoangCach; }
std::string ChuyenXe::getNgayKhoiHanh() const { return ngayKhoiHanh; }
std::string ChuyenXe::getGioKhoiHanh() const { return gioKhoiHanh; }
std::string ChuyenXe::getTenTaiXe() const { return tenTaiXe; }
int ChuyenXe::getSoHanhKhach() const { return soHanhKhach; }

void ChuyenXe::setNoiDi(std::string di) { noiDi = di; }
void ChuyenXe::setNoiDen(std::string den) { noiDen = den; }
void ChuyenXe::setBienSoXe(std::string bienSo) { bienSoXe = bienSo; }
void ChuyenXe::setKhoangCach(double kc) { khoangCach = kc; }
void ChuyenXe::setNgayKhoiHanh(std::string ngay) { ngayKhoiHanh = ngay; }
void ChuyenXe::setGioKhoiHanh(std::string gio) { gioKhoiHanh = gio; }
void ChuyenXe::setTenTaiXe(std::string taiXe) { tenTaiXe = taiXe; }
void ChuyenXe::setSoHanhKhach(int soHK) { soHanhKhach = soHK; }

void ChuyenXe::tangHanhKhach() { soHanhKhach++; }
void ChuyenXe::giamHanhKhach() { if (soHanhKhach > 0) soHanhKhach--; }

std::string ChuyenXe::toCSV() const {
    return std::to_string(getType()) + "," + maChuyen + "," + noiDi + "," + noiDen + "," + bienSoXe + "," + std::to_string(khoangCach) + "," + ngayKhoiHanh + "," + gioKhoiHanh + "," + tenTaiXe + "," + std::to_string(soHanhKhach);
}

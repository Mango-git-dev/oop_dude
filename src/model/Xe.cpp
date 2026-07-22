#include "Xe.h"

Xe::Xe(std::string bien, std::string loai, int ghe)
    : bienSo(bien), loaiXe(loai), soGhe(ghe) {}

std::string Xe::getBienSo() const { return bienSo; }
std::string Xe::getLoaiXe() const { return loaiXe; }
int Xe::getSoGhe() const { return soGhe; }

void Xe::setLoaiXe(std::string loai) { loaiXe = loai; }
void Xe::setSoGhe(int ghe) { soGhe = ghe; }

std::string Xe::toCSV() const {
    return bienSo + "," + loaiXe + "," + std::to_string(soGhe);
}

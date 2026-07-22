#include "Ve.h"
#include <string>

Ve::Ve(std::string id, std::string idChuyen, std::string idHanhKhach, double gia)
    : maVe(id), maChuyenXe(idChuyen), cccdHanhKhach(idHanhKhach), giaTien(gia) {}

std::string Ve::getMaVe() const { return maVe; }
std::string Ve::getMaChuyenXe() const { return maChuyenXe; }
std::string Ve::getCCCDHanhKhach() const { return cccdHanhKhach; }
double Ve::getGiaTien() const { return giaTien; }

void Ve::setMaChuyenXe(std::string idChuyen) { maChuyenXe = idChuyen; }
void Ve::setCCCDHanhKhach(std::string idHanhKhach) { cccdHanhKhach = idHanhKhach; }
void Ve::setGiaTien(double gia) { giaTien = gia; }

std::string Ve::toCSV() const {
    return maVe + "," + maChuyenXe + "," + cccdHanhKhach + "," + std::to_string(giaTien);
}

#include "Ve.h"
#include <string>

Ve::Ve(std::string id, std::string idChuyen, std::string idHanhKhach, double gia, std::string di, std::string den)
    : maVe(id), maChuyenXe(idChuyen), cccdHanhKhach(idHanhKhach), giaTien(gia), noiDi(di), noiDen(den) {}

std::string Ve::getMaVe() const { return maVe; }
std::string Ve::getMaChuyenXe() const { return maChuyenXe; }
std::string Ve::getCCCDHanhKhach() const { return cccdHanhKhach; }
double Ve::getGiaTien() const { return giaTien; }
std::string Ve::getNoiDi() const { return noiDi; }
std::string Ve::getNoiDen() const { return noiDen; }

void Ve::setMaChuyenXe(std::string idChuyen) { maChuyenXe = idChuyen; }
void Ve::setCCCDHanhKhach(std::string idHanhKhach) { cccdHanhKhach = idHanhKhach; }
void Ve::setGiaTien(double gia) { giaTien = gia; }
void Ve::setNoiDi(std::string di) { noiDi = di; }
void Ve::setNoiDen(std::string den) { noiDen = den; }

std::string Ve::toCSV() const {
    return maVe + "," + maChuyenXe + "," + cccdHanhKhach + "," + std::to_string(giaTien) + "," + noiDi + "," + noiDen;
}

#include "HanhKhach.h"

HanhKhach::HanhKhach(std::string id, std::string name, std::string phone)
    : cccd(id), ten(name), sdt(phone) {}

std::string HanhKhach::getCCCD() const { return cccd; }
std::string HanhKhach::getTen() const { return ten; }
std::string HanhKhach::getSDT() const { return sdt; }

void HanhKhach::setTen(std::string name) { ten = name; }
void HanhKhach::setSDT(std::string phone) { sdt = phone; }

std::string HanhKhach::toCSV() const {
    return cccd + "," + ten + "," + sdt;
}

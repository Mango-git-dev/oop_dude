#ifndef CHUYENXEVIP_H
#define CHUYENXEVIP_H

#include "ChuyenXe.h"
#include <string>

class ChuyenXeVIP : public ChuyenXe {
private:
    double phiDichVu;
public:
    ChuyenXeVIP(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string taiXe, double phi);
    
    double tinhDoanhThu() const override;
    int getType() const override;
    
    void setPhiDichVu(double phi);
    
    std::string toCSV() const override;
};

#endif // CHUYENXEVIP_H

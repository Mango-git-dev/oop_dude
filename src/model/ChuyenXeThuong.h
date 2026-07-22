#ifndef CHUYENXETHUONG_H
#define CHUYENXETHUONG_H

#include "ChuyenXe.h"

class ChuyenXeThuong : public ChuyenXe {
public:
    ChuyenXeThuong(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string taiXe);
    
    double tinhDoanhThu() const override;
    int getType() const override;
};

#endif // CHUYENXETHUONG_H

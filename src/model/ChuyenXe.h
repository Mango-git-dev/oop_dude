#ifndef CHUYENXE_H
#define CHUYENXE_H

#include <string>

class ChuyenXe {
protected:
    std::string maChuyen;
    std::string noiDi;
    std::string noiDen;
    std::string bienSoXe;
    double khoangCach;
    std::string ngayKhoiHanh;
    std::string tenTaiXe;

public:
    ChuyenXe(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string taiXe);
    virtual ~ChuyenXe() = default;

    std::string getMaChuyen() const;
    std::string getNoiDi() const;
    std::string getNoiDen() const;
    std::string getBienSoXe() const;
    double getKhoangCach() const;
    std::string getNgayKhoiHanh() const;
    std::string getTenTaiXe() const;

    void setNoiDi(std::string di);
    void setNoiDen(std::string den);
    void setBienSoXe(std::string bienSo);
    void setKhoangCach(double kc);
    void setNgayKhoiHanh(std::string ngay);
    void setTenTaiXe(std::string taiXe);

    // Pure virtual function
    virtual double tinhDoanhThu() const = 0;
    
    // Type identifier for CSV
    virtual int getType() const = 0;

    virtual std::string toCSV() const;
};

#endif // CHUYENXE_H

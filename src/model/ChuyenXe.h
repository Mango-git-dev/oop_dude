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
    std::string gioKhoiHanh;
    std::string tenTaiXe;
    int soHanhKhach;

public:
    ChuyenXe(std::string ma, std::string di, std::string den, std::string bienSo, double khoangCach, std::string ngay, std::string gio, std::string taiXe, int soHK = 0);
    virtual ~ChuyenXe() = default;
    //interface
    std::string getMaChuyen() const;
    std::string getNoiDi() const;
    std::string getNoiDen() const;
    std::string getBienSoXe() const;
    double getKhoangCach() const;
    std::string getNgayKhoiHanh() const;
    std::string getGioKhoiHanh() const;
    std::string getTenTaiXe() const;
    int getSoHanhKhach() const;

    void setNoiDi(std::string di);
    void setNoiDen(std::string den);
    void setBienSoXe(std::string bienSo);
    void setKhoangCach(double kc);
    void setNgayKhoiHanh(std::string ngay);
    void setGioKhoiHanh(std::string gio);
    void setTenTaiXe(std::string taiXe);
    void setSoHanhKhach(int soHK);
    void tangHanhKhach();
    void giamHanhKhach();

    //ham ao
    virtual double tinhGiaVe() const = 0;

    virtual int getType() const = 0;

    virtual std::string toCSV() const;
};

#endif // CHUYENXE_H

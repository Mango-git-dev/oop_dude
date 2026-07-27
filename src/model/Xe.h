#ifndef XE_H
#define XE_H

#include <string>

class Xe {
private:
    std::string bienSo;
    std::string loaiXe;
    int soGhe;

public:
    Xe(std::string bien, std::string loai, int ghe);
    
    std::string getBienSo() const;
    std::string getLoaiXe() const;
    int getSoGhe() const;
    
    void setLoaiXe(std::string loai);
    void setSoGhe(int ghe);
    
    std::string toCSV() const;
};

#endif // XE_H

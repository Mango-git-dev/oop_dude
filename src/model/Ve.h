#ifndef VE_H
#define VE_H

#include <string>

class Ve {
private:
    std::string maVe;
    std::string maChuyenXe;
    std::string cccdHanhKhach;
    double giaTien;
    std::string noiDi;
    std::string noiDen;

public:
    Ve(std::string id, std::string idChuyen, std::string idHanhKhach, double gia, std::string di, std::string den);
    
    std::string getMaVe() const;
    std::string getMaChuyenXe() const;
    std::string getCCCDHanhKhach() const;
    double getGiaTien() const;
    std::string getNoiDi() const;
    std::string getNoiDen() const;
    
    void setMaChuyenXe(std::string idChuyen);
    void setCCCDHanhKhach(std::string idHanhKhach);
    void setGiaTien(double gia);
    void setNoiDi(std::string di);
    void setNoiDen(std::string den);
    
    std::string toCSV() const;
};

#endif // VE_H

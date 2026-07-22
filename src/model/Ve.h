#ifndef VE_H
#define VE_H

#include <string>

class Ve {
private:
    std::string maVe;
    std::string maChuyenXe;
    std::string cccdHanhKhach;
    double giaTien;

public:
    Ve(std::string id, std::string idChuyen, std::string idHanhKhach, double gia);
    
    std::string getMaVe() const;
    std::string getMaChuyenXe() const;
    std::string getCCCDHanhKhach() const;
    double getGiaTien() const;
    
    void setMaChuyenXe(std::string idChuyen);
    void setCCCDHanhKhach(std::string idHanhKhach);
    void setGiaTien(double gia);
    
    std::string toCSV() const;
};

#endif // VE_H

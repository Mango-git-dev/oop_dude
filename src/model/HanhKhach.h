#ifndef HANHKHACH_H
#define HANHKHACH_H

#include <string>

class HanhKhach {
private:
    std::string cccd;
    std::string ten;
    std::string sdt;

public:
    HanhKhach(std::string id, std::string name, std::string phone);
    
    std::string getCCCD() const;
    std::string getTen() const;
    std::string getSDT() const;
    
    void setTen(std::string name);
    void setSDT(std::string phone);
    
    std::string toCSV() const;
};

#endif // HANHKHACH_H

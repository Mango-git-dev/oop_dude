#ifndef XECONTROLLER_H
#define XECONTROLLER_H

#include <map>
#include <string>
#include "../model/Xe.h"
#include "../model/ChuyenXe.h"
#include "../view/ConsoleView.h"

class XeController {
private:
    std::map<std::string, Xe>& danhSachXe;
    std::map<std::string, ChuyenXe*>& danhSachChuyenXe;
    const ConsoleView& view;

public:
    XeController(std::map<std::string, Xe>& dsXe, std::map<std::string, ChuyenXe*>& dsChuyen, const ConsoleView& consoleView);

    void themXe();
    void xoaXe();
    void timKiemXe();
    void suaThongTinXe();
    void hienThiToanBoXe();

    int getSucChuaXe(const std::string& bienSo) const;
    std::string chonBienSoXe(const std::string& promptMsg) const;
};

#endif // XECONTROLLER_H


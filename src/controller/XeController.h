#ifndef XECONTROLLER_H
#define XECONTROLLER_H

#include <map>
#include <string>
#include "../model/Xe.h"
#include "../view/ConsoleView.h"

class XeController {
private:
    std::map<std::string, Xe>& danhSachXe;
    const ConsoleView& view;

public:
    XeController(std::map<std::string, Xe>& dsXe, const ConsoleView& consoleView);

    void themXe();
    void xoaXe();
    void timKiemXe();
    void suaThongTinXe();
    void hienThiToanBoXe();

    int getSucChuaXe(const std::string& bienSo) const;
    std::string chonBienSoXe(const std::string& promptMsg) const;
};

#endif // XECONTROLLER_H

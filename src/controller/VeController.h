#ifndef VECONTROLLER_H
#define VECONTROLLER_H

#include <vector>
#include <map>
#include <string>
#include "../model/Ve.h"
#include "../model/HanhKhach.h"
#include "../model/ChuyenXe.h"
#include "../view/ConsoleView.h"
#include "XeController.h"

class VeController {
private:
    std::vector<Ve>& danhSachVe;
    std::map<std::string, HanhKhach>& danhSachHanhKhach;
    std::map<std::string, ChuyenXe*>& danhSachChuyenXe;
    const XeController& xeController;
    const ConsoleView& view;

public:
    VeController(std::vector<Ve>& dsVe, std::map<std::string, HanhKhach>& dsHK, std::map<std::string, ChuyenXe*>& dsChuyen, const XeController& xeCtrl, const ConsoleView& consoleView);

    std::string generateMaVe() const;
    int chonIndexVe(const std::string& promptMsg) const;

    void datVeKhachHang();
    void traCuuVeKhachHang();
    void huyVeKhachHang();

    void huyVeQuanLy();
    void timKiemVe();
    void suaThongTinVe();
    void hienThiDanhSachVe();
    void traCuuKhachHang();
};

#endif // VECONTROLLER_H

#ifndef CHUYENXECONTROLLER_H
#define CHUYENXECONTROLLER_H

#include <map>
#include <vector>
#include <string>
#include "../model/ChuyenXe.h"
#include "../model/Ve.h"
#include "../view/ConsoleView.h"
#include "XeController.h"

class ChuyenXeController {
private:
    std::map<std::string, ChuyenXe*>& danhSachChuyenXe;
    std::vector<Ve>& danhSachVe;
    const XeController& xeController;
    const ConsoleView& view;

public:
    ChuyenXeController(std::map<std::string, ChuyenXe*>& dsChuyen, std::vector<Ve>& dsVe, const XeController& xeCtrl, const ConsoleView& consoleView);

    std::string generateMaChuyen() const;
    std::string chonMaChuyen(const std::string& promptMsg) const;
    int demHanhKhachTheoChuyen(const std::string& maChuyen) const;
    void capNhatSoHanhKhachTatCa();

    void themChuyen();
    void huyChuyen();
    void timKiemChuyen();
    void suaThongTinChuyen();
    void hienThiDanhSachChuyen();
    void sapXepChuyen();
    void traCuuTaiXe();
    void xemLichTrinhTrongNgay();
};

#endif // CHUYENXECONTROLLER_H

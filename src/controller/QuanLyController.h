#ifndef QUANLYCONTROLLER_H
#define QUANLYCONTROLLER_H

#include <vector>
#include <map>
#include "../model/Xe.h"
#include "../model/HanhKhach.h"
#include "../model/Ve.h"
#include "../model/ChuyenXe.h"
#include "../view/ConsoleView.h"

class QuanLyController {
private:
    std::map<std::string, Xe> danhSachXe;                // key: bienSo
    std::map<std::string, HanhKhach> danhSachHanhKhach;  // key: cccd
    std::vector<Ve> danhSachVe;                          // ve van dung vector
    std::map<std::string, ChuyenXe*> danhSachChuyenXe;   // key: maChuyen
    ConsoleView view;

    void loadData();
    void saveData() const;

    // Helper methods
    int demHanhKhachTheoChuyen(const std::string& maChuyen) const;
    void capNhatSoHanhKhachTatCa();
    int getSucChuaXe(const std::string& bienSo) const;

public:
    QuanLyController();
    ~QuanLyController();

    void start();

    // xe
    void themXe();
    void xoaXe();
    void timKiemXe();
    void suaThongTinXe();
    void hienThiToanBoXe();

    // quan ly Chuyen
    void themChuyen();
    void huyChuyen();
    void timKiemChuyen();
    void suaThongTinChuyen();
    void hienThiDanhSachChuyen();
    void sapXepChuyen();

    // quan ly Ve
    void datVe();
    void huyVe();
    void timKiemVe();
    void suaThongTinVe();
    void hienThiDanhSachVe();

    // tong quan
    void thongKeTongQuat();
    void xemLichTrinhTrongNgay();
    void traCuuTaiXe();
    void traCuuKhachHang();
};

#endif // QUANLYCONTROLLER_H

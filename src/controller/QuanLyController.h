#ifndef QUANLYCONTROLLER_H
#define QUANLYCONTROLLER_H

#include <vector>
#include "../model/Xe.h"
#include "../model/HanhKhach.h"
#include "../model/Ve.h"
#include "../model/ChuyenXe.h"
#include "../view/ConsoleView.h"

class QuanLyController {
private:
    std::vector<Xe> danhSachXe;
    std::vector<HanhKhach> danhSachHanhKhach;
    std::vector<Ve> danhSachVe;
    std::vector<ChuyenXe*> danhSachChuyenXe;
    ConsoleView view;

    void loadData();
    void saveData() const;

public:
    QuanLyController();
    ~QuanLyController();

    void start();

    // Quan ly Xe
    void themXe();
    void xoaXe();
    void timKiemXe();
    void suaThongTinXe();
    void hienThiToanBoXe();

    // Quan ly Chuyen
    void themChuyen();
    void huyChuyen();
    void timKiemChuyen();
    void suaThongTinChuyen();
    void hienThiDanhSachChuyen();
    void sapXepChuyen();

    // Quan ly Ve
    void datVe();
    void huyVe();
    void timKiemVe();
    void suaThongTinVe();
    void hienThiDanhSachVe();

    // Tong quan
    void thongKeTongQuat();
    void xemLichTrinhTrongNgay();
    void traCuuTaiXe();
    void traCuuKhachHang();
};

#endif // QUANLYCONTROLLER_H

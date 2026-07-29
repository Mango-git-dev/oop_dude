#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <vector>
#include <map>
#include "../model/Xe.h"
#include "../model/HanhKhach.h"
#include "../model/Ve.h"
#include "../model/ChuyenXe.h"

class DataManager {
private:
    static std::vector<std::string> splitString(const std::string& s, char delimiter);

public:
    static void loadXe(std::map<std::string, Xe>& danhSachXe, const std::string& filename = "data/xe.csv");
    static void saveXe(const std::map<std::string, Xe>& danhSachXe, const std::string& filename = "data/xe.csv");

    static void loadHanhKhach(std::map<std::string, HanhKhach>& danhSachHanhKhach, const std::string& filename = "data/hanh_khach.csv");
    static void saveHanhKhach(const std::map<std::string, HanhKhach>& danhSachHanhKhach, const std::string& filename = "data/hanh_khach.csv");

    static void loadVe(std::vector<Ve>& danhSachVe, const std::string& filename = "data/ve.csv");
    static void saveVe(const std::vector<Ve>& danhSachVe, const std::string& filename = "data/ve.csv");

    static void loadChuyenXe(std::map<std::string, ChuyenXe*>& danhSachChuyenXe, const std::string& filename = "data/chuyen_xe.csv");
    static void saveChuyenXe(const std::map<std::string, ChuyenXe*>& danhSachChuyenXe, const std::string& filename = "data/chuyen_xe.csv");

    static void loadAll(
        std::map<std::string, Xe>& danhSachXe,
        std::map<std::string, HanhKhach>& danhSachHanhKhach,
        std::vector<Ve>& danhSachVe,
        std::map<std::string, ChuyenXe*>& danhSachChuyenXe
    );

    static void saveAll(
        const std::map<std::string, Xe>& danhSachXe,
        const std::map<std::string, HanhKhach>& danhSachHanhKhach,
        const std::vector<Ve>& danhSachVe,
        const std::map<std::string, ChuyenXe*>& danhSachChuyenXe
    );
};

#endif // DATAMANAGER_H

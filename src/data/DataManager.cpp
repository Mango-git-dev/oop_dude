#include "DataManager.h"
#include "../exception/CustomException.h"
#include "../model/ChuyenXeThuong.h"
#include "../model/ChuyenXeVIP.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> DataManager::splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        size_t first = token.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            size_t last = token.find_last_not_of(" \t\r\n");
            token = token.substr(first, last - first + 1);
        } else {
            token = "";
        }
        tokens.push_back(token);
    }
    return tokens;
}

void DataManager::loadXe(std::map<std::string, Xe>& danhSachXe, const std::string& filename) {
    std::ifstream fileXe(filename);
    if (!fileXe.is_open()) return;

    std::string line;
    bool firstLine = true;
    while (std::getline(fileXe, line)) {
        if (firstLine) { firstLine = false; continue; }
        if (line.empty() || line == "\r") continue;
        auto tokens = splitString(line, ',');
        if (tokens.size() >= 3) {
            if (danhSachXe.count(tokens[0])) {
                std::cout << "[WARNING] Du lieu file " << filename << " bi TRUNG BIEN SO [" << tokens[0]
                          << "] - dong nay bi bo qua: " << line << "\n";
            } else {
                danhSachXe.emplace(tokens[0], Xe(tokens[0], tokens[1], std::stoi(tokens[2])));
            }
        }
    }
    fileXe.close();
}

void DataManager::saveXe(const std::map<std::string, Xe>& danhSachXe, const std::string& filename) {
    std::ofstream fileXe(filename);
    if (!fileXe) throw FileException("Cannot open " + filename + " for writing");
    fileXe << "BienSo,LoaiXe,SucChua\n";
    for (const auto& entry : danhSachXe) {
        fileXe << entry.second.toCSV() << "\n";
    }
}

void DataManager::loadHanhKhach(std::map<std::string, HanhKhach>& danhSachHanhKhach, const std::string& filename) {
    std::ifstream fileHK(filename);
    if (!fileHK.is_open()) return;

    std::string line;
    bool firstLine = true;
    while (std::getline(fileHK, line)) {
        if (firstLine) { firstLine = false; continue; }
        if (line.empty() || line == "\r") continue;
        auto tokens = splitString(line, ',');
        if (tokens.size() >= 3) {
            if (danhSachHanhKhach.count(tokens[0])) {
                std::cout << "[WARNING] Du lieu file " << filename << " bi TRUNG CCCD [" << tokens[0]
                          << "] - dong nay bi bo qua: " << line << "\n";
            } else {
                danhSachHanhKhach.emplace(tokens[0], HanhKhach(tokens[0], tokens[1], tokens[2]));
            }
        }
    }
    fileHK.close();
}

void DataManager::saveHanhKhach(const std::map<std::string, HanhKhach>& danhSachHanhKhach, const std::string& filename) {
    std::ofstream fileHK(filename);
    if (!fileHK) throw FileException("Cannot open " + filename + " for writing");
    fileHK << "CCCD,HoTen,SDT\n";
    for (const auto& entry : danhSachHanhKhach) {
        fileHK << entry.second.toCSV() << "\n";
    }
}

void DataManager::loadVe(std::vector<Ve>& danhSachVe, const std::string& filename) {
    std::ifstream fileVe(filename);
    if (!fileVe.is_open()) return;

    std::string line;
    bool firstLine = true;
    while (std::getline(fileVe, line)) {
        if (firstLine) { firstLine = false; continue; }
        if (line.empty() || line == "\r") continue;
        auto tokens = splitString(line, ',');
        if (tokens.size() >= 6) {
            danhSachVe.emplace_back(tokens[0], tokens[1], tokens[2], std::stod(tokens[3]), tokens[4], tokens[5]);
        }
    }
    fileVe.close();
}

void DataManager::saveVe(const std::vector<Ve>& danhSachVe, const std::string& filename) {
    std::ofstream fileVe(filename);
    if (!fileVe) throw FileException("Cannot open " + filename + " for writing");
    fileVe << "MaVe,MaChuyenXe,CCCD,GiaTien,NoiDi,NoiDen\n";
    for (const auto& ve : danhSachVe) {
        fileVe << ve.toCSV() << "\n";
    }
}

void DataManager::loadChuyenXe(std::map<std::string, ChuyenXe*>& danhSachChuyenXe, const std::string& filename) {
    std::ifstream fileCX(filename);
    if (!fileCX.is_open()) return;

    std::string line;
    bool firstLine = true;
    while (std::getline(fileCX, line)) {
        if (firstLine) { firstLine = false; continue; }
        if (line.empty() || line == "\r") continue;
        auto tokens = splitString(line, ',');
        if (tokens.size() >= 10) {
            int type = std::stoi(tokens[0]);
            std::string ma = tokens[1];
            std::string di = tokens[2];
            std::string den = tokens[3];
            std::string bien = tokens[4];
            double kc = std::stod(tokens[5]);
            std::string ngay = tokens[6];
            std::string gio = tokens[7];
            std::string taiXe = tokens[8];
            int soHK = std::stoi(tokens[9]);

            if (danhSachChuyenXe.count(ma)) {
                std::cout << "[WARNING] Du lieu file " << filename << " bi TRUNG MA CHUYEN [" << ma
                          << "] - dong nay bi bo qua: " << line << "\n";
            } else if (type == 1) {
                danhSachChuyenXe[ma] = new ChuyenXeThuong(ma, di, den, bien, kc, ngay, gio, taiXe, soHK);
            } else if (type == 2 && tokens.size() >= 11) {
                double phi = std::stod(tokens[10]);
                danhSachChuyenXe[ma] = new ChuyenXeVIP(ma, di, den, bien, kc, ngay, gio, taiXe, phi, soHK);
            }
        }
    }
    fileCX.close();
}

void DataManager::saveChuyenXe(const std::map<std::string, ChuyenXe*>& danhSachChuyenXe, const std::string& filename) {
    std::ofstream fileCX(filename);
    if (!fileCX) throw FileException("Cannot open " + filename + " for writing");
    fileCX << "Loai,MaChuyen,NoiDi,NoiDen,BienSoXe,KhoangCach,NgayKhoiHanh,GioKhoiHanh,TenTaiXe,SoHanhKhach,PhiDichVu\n";
    for (const auto& entry : danhSachChuyenXe) {
        fileCX << entry.second->toCSV() << "\n";
    }
}

void DataManager::loadAll(
    std::map<std::string, Xe>& danhSachXe,
    std::map<std::string, HanhKhach>& danhSachHanhKhach,
    std::vector<Ve>& danhSachVe,
    std::map<std::string, ChuyenXe*>& danhSachChuyenXe
) {
    loadXe(danhSachXe);
    loadHanhKhach(danhSachHanhKhach);
    loadVe(danhSachVe);
    loadChuyenXe(danhSachChuyenXe);
}

void DataManager::saveAll(
    const std::map<std::string, Xe>& danhSachXe,
    const std::map<std::string, HanhKhach>& danhSachHanhKhach,
    const std::vector<Ve>& danhSachVe,
    const std::map<std::string, ChuyenXe*>& danhSachChuyenXe
) {
    saveXe(danhSachXe);
    saveHanhKhach(danhSachHanhKhach);
    saveVe(danhSachVe);
    saveChuyenXe(danhSachChuyenXe);
}

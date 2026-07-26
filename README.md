# 📊 BÁO CÁO TÍNH NĂNG CHI TIẾT — Quản Lý Xe & Chuyến Xe (OOP CMC)

**Ngày cập nhật:** 26/07/2026  
**Tổng tính năng:** 25 | **✅ Hoàn thành:** 25 (100%) | **❌ Chưa làm:** 0

---

## 📑 Mục Lục

1. [Menu Khách Hàng (Customer Menu)](#1-menu-khách-hàng-customer-menu---33-100)
2. [Menu Quản Lý — Đội Xe (Vehicle Management)](#2-menu-quản-lý--đội-xe-vehicle-management---55-100)
3. [Menu Quản Lý — Chuyến Xe (Trip Management)](#3-menu-quản-lý--chuyến-xe-trip-management---88-100)
4. [Menu Quản Lý — Vé & Hành Khách (Ticket & Passenger Management)](#4-menu-quản-lý--vé--hành-khách-ticket--passenger-management---55-100)
5. [Menu Báo Cáo & Thống Kê (Dashboard & Statistics)](#5-menu-báo-cáo--thống-kê-dashboard--statistics---11-100)
6. [Cải thiện Kiến trúc & Thiết kế OOP (Architecture & OOP Design)](#6-cải-thiện-kiến-trúc--thiết-kế-oop-architecture--oop-design---33-100)
7. [Tổng Kết](#-tổng-kết)

---

## 1. Menu Khách Hàng (Customer Menu) — ✅ 3/3 (100%)

| # | Tính năng | Trạng thái | File liên quan | Chi tiết |
|:-:|-----------|:---:|----------------|---------|
| 1 | Đặt vé xe khách | ✅ | `VeController.cpp`, `ConsoleView.cpp` | Hiển thị danh sách chuyến xe khả dụng (còn chỗ), nhập CCCD, họ tên, SĐT, tự động đăng ký hành khách mới nếu chưa có, sinh mã vé tự động (`VE01`, `VE02`...), cập nhật số hành khách trên chuyến |
| 2 | Tra cứu vé khách hàng | ✅ | `VeController.cpp`, `ConsoleView.cpp` | Cho phép hành khách tìm kiếm vé đã đặt theo Mã vé hoặc Số CCCD cá nhân, hiển thị thông tin chuyến xe, tuyến đường và giá vé |
| 3 | Hủy vé khách hàng | ✅ | `VeController.cpp`, `ConsoleView.cpp` | Cho phép khách hàng tự hủy vé đã đặt bằng cách xác minh Mã vé và Số CCCD, giảm số lượng hành khách trên chuyến xe tương ứng |

---

## 2. Menu Quản Lý — Đội Xe (Vehicle Management) — ✅ 5/5 (100%)

| # | Tính năng | Trạng thái | File liên quan | Chi tiết |
|:-:|-----------|:---:|----------------|---------|
| 1 | Thêm xe mới | ✅ | `XeController.cpp`, `Xe.cpp` | Nhập biển số xe (kiểm tra trùng lặp), loại xe (Hyundai Universe, Thaco Mobihome, Ford Transit...), sức chứa (số ghế), lưu vào danh sách quản lý |
| 2 | Xóa thông tin xe | ✅ | `XeController.cpp` | Cho phép xóa xe khỏi hệ thống. Kiểm tra an toàn: Không cho phép xóa xe nếu xe đang được gán cho một chuyến xe active |
| 3 | Tìm kiếm xe | ✅ | `XeController.cpp` | Tìm kiếm linh hoạt theo Biển số xe hoặc theo Loại xe (không phân biệt chữ hoa/thường) |
| 4 | Chỉnh sửa thông tin xe | ✅ | `XeController.cpp` | Cập nhật Loại xe hoặc Sức chứa số ghế của xe theo biển số đã chọn |
| 5 | Hiển thị toàn bộ đội xe | ✅ | `XeController.cpp`, `ConsoleView.cpp` | In bảng danh sách toàn bộ các xe trong hệ thống với các cột: Biển số, Loại xe, Sức chứa |

---

## 3. Menu Quản Lý — Chuyến Xe (Trip Management) — ✅ 8/8 (100%)

| # | Tính năng | Trạng thái | File liên quan | Chi tiết |
|:-:|-----------|:---:|----------------|---------|
| 1 | Thêm chuyến xe mới | ✅ | `ChuyenXeController.cpp`, `ChuyenXeThuong.cpp`, `ChuyenXeVIP.cpp` | Sinh mã chuyến tự động (`CX01`, `CX02`...), chọn Loại (Thường/VIP), Nơi đi, Nơi đến, Phân công biển số xe từ danh sách, Khoảng cách (km), Ngày/Giờ khởi hành, Tên tài xế, Phí dịch vụ (nếu là VIP) |
| 2 | Hủy / Xóa chuyến xe | ✅ | `ChuyenXeController.cpp` | Xóa chuyến xe khỏi danh sách. Kiểm tra ràng buộc: Nếu chuyến xe đã có vé đặt, thông báo cảnh báo và hỗ trợ tự động hủy các vé liên quan trước khi xóa |
| 3 | Tìm kiếm chuyến xe | ✅ | `ChuyenXeController.cpp` | Tìm kiếm đa tiêu chí: theo Mã chuyến, Nơi đi, Nơi đến, hoặc Ngày khởi hành |
| 4 | Chỉnh sửa chuyến xe | ✅ | `ChuyenXeController.cpp` | Cho phép sửa Nơi đi, Nơi đến, Biển số xe phân công, Khoảng cách, Ngày/Giờ khởi hành, Tên tài xế, Phí dịch vụ VIP |
| 5 | Hiển thị danh sách chuyến xe | ✅ | `ChuyenXeController.cpp`, `ConsoleView.cpp` | Định dạng bảng danh sách đầy đủ thông tin: Loại chuyến, Mã, Tuyến đường, Biển số, Khoảng cách, Ngày/Giờ chạy, Tài xế, Số khách, Doanh thu ước tính |
| 6 | Sắp xếp danh sách chuyến xe | ✅ | `ChuyenXeController.cpp` | Sắp xếp theo 3 tiêu chí: Giờ khởi hành tăng dần, Doanh thu giảm dần, Mã chuyến xe |
| 7 | Xem lịch trình trong ngày | ✅ | `ChuyenXeController.cpp` | Nhập ngày (DD/MM/YYYY) để lọc và hiển thị toàn bộ lịch trình xuất bến của các chuyến xe trong ngày đó |
| 8 | Tra cứu theo tài xế | ✅ | `ChuyenXeController.cpp` | Tìm kiếm tất cả các chuyến xe do một tài xế cụ thể phụ trách lái theo tên tài xế |

---

## 4. Menu Quản Lý — Vé & Hành Khách (Ticket & Passenger Management) — ✅ 5/5 (100%)

| # | Tính năng | Trạng thái | File liên quan | Chi tiết |
|:-:|-----------|:---:|----------------|---------|
| 1 | Hủy vé (Quyền Quản lý) | ✅ | `VeController.cpp` | Quản lý tìm và hủy bất kỳ vé nào trong hệ thống theo Mã vé |
| 2 | Tìm kiếm vé bán | ✅ | `VeController.cpp` | Tra cứu vé theo Mã vé, Mã chuyến xe hoặc Số CCCD của hành khách |
| 3 | Chỉnh sửa thông tin vé | ✅ | `VeController.cpp` | Cho phép sửa thông tin chuyến xe đã đăng ký trên vé hoặc đổi thông tin CCCD người đi |
| 4 | Hiển thị danh sách vé | ✅ | `VeController.cpp`, `ConsoleView.cpp` | Bảng tổng hợp toàn bộ vé đã xuất: Mã vé, Mã chuyến, CCCD khách, Giá vé, Tuyến đi/đến |
| 5 | Tra cứu danh bạ hành khách | ✅ | `VeController.cpp` | Tra cứu thông tin hành khách (Họ tên, SĐT, Lịch sử các vé đã mua) theo CCCD hoặc SĐT |

---

## 5. Menu Báo Cáo & Thống Kê (Dashboard & Statistics) — ✅ 1/1 (100%)

| # | Tính năng | Trạng thái | File liên quan | Chi tiết |
|:-:|-----------|:---:|----------------|---------|
| 1 | Báo cáo Thống kê Tổng quát | ✅ | `MainController.cpp`, `ConsoleView.cpp` | Hiển thị Dashboard tổng quan: Tổng số xe, Tổng số chuyến xe, Tổng số hành khách, Tổng số vé đã bán và **Tổng doanh thu dự kiến toàn hệ thống** (tính đa hình theo từng loại chuyến xe) |

---

## 6. Cải thiện Kiến trúc & Thiết kế OOP (Architecture & OOP Design) — ✅ 3/3 (100%)

### 6.1 Áp dụng Tính Đa hình & Kế thừa (Polymorphic Core)

```
                       ┌─────────────────────────┐
                       │   ChuyenXe (Abstract)   │
                       └────────────┬────────────┘
                                    │
           ┌────────────────────────┴────────────────────────┐
           ▼                                                 ▼
┌───────────────────────┐                         ┌───────────────────────┐
│   ChuyenXeThuong      │                         │      ChuyenXeVIP      │
├───────────────────────┤                         ├───────────────────────┤
│ DoanhThu = kc * 10k   │                         │ DoanhThu = kc * 15k   │
│                       │                         │            + PhiDichVu│
└───────────────────────┘                         └───────────────────────┘
```

- **Lớp cơ sở trừu tượng `ChuyenXe`**: Định nghĩa giao diện chung cho mọi loại chuyến xe.
- **Phương thức ảo `tinhDoanhThu()`**:
  - `ChuyenXeThuong`: Tính doanh thu = $\text{Khoảng cách} \times 10.000\text{ VNĐ/km}$.
  - `ChuyenXeVIP`: Tính doanh thu = $(\text{Khoảng cách} \times 15.000\text{ VNĐ/km}) + \text{Phí dịch vụ}$.

### 6.2 Mô hình MVC & Lưu trữ CSV 

| Lớp kiến trúc | Thư mục / File | Vai trò & Trách nhiệm |
|---------------|----------------|----------------------|
| **Model** | `src/model/` | Chứa các đối tượng thực thể: `Xe`, `ChuyenXe`, `ChuyenXeThuong`, `ChuyenXeVIP`, `HanhKhach`, `Ve`. |
| **View** | `src/view/` | `ConsoleView`: Xử lý giao diện dòng lệnh, nhập xuất dữ liệu, định dạng bảng hiển thị. |
| **Controller** | `src/controller/` | `MainController`, `XeController`, `ChuyenXeController`, `VeController`: Xử lý logic nghiệp vụ. |
| **Data Access Layer** | `src/data/` | `DataManager`: Đọc/Ghi dữ liệu tự động ra 4 file CSV (`xe.csv`, `chuyen_xe.csv`, `hanh_khach.csv`, `ve.csv`). |
| **Utility & Exception** | `src/controller/`, `src/exception/` | `StringUtil` (Chuẩn hóa Title Case, Trim, Lowercase), `CustomException` (Xử lý ngoại lệ an toàn). |

### 6.3 Kiểm tra dữ liệu & Xử lý ngoại lệ (Validation & Exceptions)

- **Tự động sinh mã thông minh**: `generateMaChuyen()`, `generateMaVe()` tìm mã lớn nhất và tự động tăng lên 1 (VD: `CX40` $\rightarrow$ `CX41`).
- **Validate định dạng**:
  - CCCD: Đủ 12 chữ số.
  - SĐT: Đủ 10 - 11 chữ số.
  - Giờ khởi hành: Đúng định dạng `HH:MM` (00:00 đến 23:59).
  - Khoảng cách: Lớn hơn 0.
- **Chuẩn hóa chuỗi (`StringUtil`)**: Tự động đưa tên người dùng, tên địa danh về dạng chuẩn Title Case (viết hoa chữ cái đầu từng từ).

---

## 🏁 Tổng Kết

Dự án **Quản Lý Xe & Chuyến Xe (OOP CMC)** được xây dựng hoàn chỉnh theo chuẩn kiến trúc **MVC (Model - View - Controller)** trong C++14, đáp ứng 100% các yêu cầu nghiệp vụ quản lý bến xe, bán vé và thống kê doanh thu:

- 🟢 **Tính năng Khách hàng:** Đặt vé, tra cứu vé, hủy vé nhanh chóng.
- 🟢 **Tính năng Quản lý:** CRUD Đội xe, Chuyến xe, Vé và Hành khách toàn diện.
- 🟢 **Kiến trúc OOP nâng cao:** Đóng gói, Kế thừa, Đa hình (Polymorphism) linh hoạt.
- 🟢 **Lưu trữ bền vững:** Tự động đồng bộ với 4 tệp dữ liệu CSV chuẩn hóa.

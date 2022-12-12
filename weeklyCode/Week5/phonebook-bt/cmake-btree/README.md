# Tổng quan
CMake build for the B-Tree library from hydrus.org.uk

### Để biên dịch các công cụ đi kèm với thư viện B-Tree
Cần bật tùy chỉnh ORIGINAL_EXECUTABLE=ON,
ví dụ có thể sử dụng lệnh: 

`cmake ../ -DORIGINAL_EXECUTABLE=ON`

Lý do không biên dịch các công cụ này ở chế độ mặc định: Vì mục đính sử dụng chính của mã nguồn này được cho là để hỗ trợ tích hợp thư viện B-Tree vào một ứng dụng khác được tạo bằng CMake

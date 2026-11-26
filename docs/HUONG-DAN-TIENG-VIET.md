# Hướng dẫn tiếng Việt — NRSuite Firmware

Bản gốc: 7wp81x/NRSuite-Firmware, GPL-3.0, FW 1.0.0.
Repo này là bản fork có thêm tiếng Việt, không đổi logic gốc.

## 1. Chỉ dùng khi được ủy quyền

Chỉ kiểm tra trên mạng và thiết bị bạn sở hữu hoặc đã được ủy quyền
rõ ràng bằng văn bản. Xem `LEGAL.md` và `SECURITY.md` ở gốc repo.

## 2. Build bản tiếng Việt

Board khuyên dùng: ESP32-C3 DevKitM-1.

```bash
pip install platformio
pio run -e esp32-c3-vi
pio run -e esp32-c3-vi --target upload
```

Env `esp32-c3-vi` nằm ở `boards/esp32-c3-vi.ini`. Nó là bản sao của
`esp32-c3`, chỉ thêm cờ `-DFIRMWARE_LANG_VI=1`.

Muốn tiếng Việt cho board khác, thêm cờ đó vào `build_flags` của
env tương ứng trong `boards/*.ini`, ví dụ:

```ini
build_flags =
    ${common_flags.build_flags}
    -DFIRMWARE_LANG_VI=1
```

Build bản tiếng Anh gốc vẫn như cũ:

```bash
pio run -e esp32-c3
```

## 3. Trang portal tiếng Việt

Trang portal thật do app Android tải lên, tối đa 24 KiB, không nằm
cứng trong firmware. Mẫu tiếng Việt ở `portal/portal-vi.html` dùng
để tải lên theo cách đó.

Trang mặc định của firmware (khi chưa tải HTML lên) đã được dịch qua
`src/lang/vi.h`: `Đang kết nối...`, tiêu đề `Kiểm tra nhận thức bảo mật`,
nút `Tiếp tục`.

## 4. Cái gì không dịch, và vì sao

App Android đọc đúng tên lệnh và khóa JSON qua USB serial, nên các
chuỗi này giữ nguyên tiếng Anh:

- Lệnh: `PING`, `STATUS`, `HEAP`, `DEAUTH`, `START_PORTAL`, ...
- Khóa JSON: `ok`, `msg`, `transport`, `pong`, ...
- Tên module, tên board, tên env PlatformIO.

Dịch các chuỗi đó sẽ làm app không nhận ra lệnh và trả lời sai.

## 5. Build tự động bằng GitHub Actions

Repo có sẵn hai workflow gốc:

- `.github/workflows/firmware-ci.yml` — build 12 env khi push lên
  `main`, `develop`, `release/**`, chạy unit test native.
- `.github/workflows/firmware-release.yml` — build và phát hành khi
  push tag `v*.*.*`.

Bản tiếng Việt thêm:

- `.github/workflows/build-firmware-vi.yml` — build các env chính
  (`esp32-c3`, `esp32-c3-vi`, `esp32-s3`, `esp32-s2`, `esp32-c5`,
  `esp32-devkit`) khi push, pull request, và khi bấm chạy tay
  (workflow_dispatch). File `.bin` trong `release/` được tải lên
  làm artifact, giữ 7 ngày.

Cách chạy tay trên GitHub:

1. Mở repo trên GitHub, vào tab **Actions**.
2. Chọn **Build Firmware (tiếng Việt)** ở cột trái.
3. Bấm **Run workflow**, chọn nhánh `main`, bấm **Run workflow**.
4. Chờ job xong, tải artifact `firmware-esp32-c3-vi` (hoặc env khác)
   ở cuối trang chạy.

Cách phát hành bản release:

```bash
git tag v1.0.0-vi.1
git push origin v1.0.0-vi.1
```

Workflow release gốc sẽ build và tạo GitHub Release kèm file `.bin`
và `checksums.txt`.

## 6. Kiểm tra sau khi build

```bash
python3 scripts/validate_targets.py
pio test -e native
python3 scripts/verify_merged_images.py --environment esp32-c3-vi
```

Trên GitHub Actions, ba bước này đã nằm trong workflow.

## 7. Thêm một chuỗi dịch mới

1. Thêm cùng một khóa vào `src/lang/en.h` và `src/lang/vi.h`.
2. Dùng khóa đó trong code qua `nrsuite::lang::kTenChuoi`.
3. Không đặt tên khóa trùng với tên lệnh JSON.

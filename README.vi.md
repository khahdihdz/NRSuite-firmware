# NRSuite Firmware — Bản tiếng Việt

> Bản dịch tiếng Việt của [README.md](./README.md) gốc, từ
> 7wp81x/NRSuite-Firmware, GPL-3.0, phiên bản ổn định 1.0.0.
> Bản gốc vẫn là tài liệu chuẩn khi có khác biệt.
> Bản tiếng Việt: [README.vi.md](./README.vi.md) | Hướng dẫn chi tiết:
> [docs/HUONG-DAN-TIENG-VIET.md](./docs/HUONG-DAN-TIENG-VIET.md)

**Firmware ESP32 cho bộ công cụ nghiên cứu bảo mật NRSuite.**

Firmware chạy trên ESP32 và giao tiếp với
[app Android NRSuite](https://github.com/7wp81x/nrsuite-android)
qua USB serial. Nó đảm nhiệm các thao tác ở tầng sóng vô tuyến:
quét Wi-Fi, bắt gói tin ở chế độ monitor, deauthentication, chèn beacon,
captive portal, BLE HID, BadUSB và lưu trữ khối, cùng các module khác
đang được lên kế hoạch.

> **Chỉ dùng khi được ủy quyền.** Firmware này chỉ dùng để nghiên cứu
> và kiểm tra bảo mật trên mạng và thiết bị mà bạn sở hữu hoặc đã được
> ủy quyền rõ ràng để kiểm tra. Xem [LEGAL.md](./LEGAL.md).

**Dòng ổn định hiện tại:** `1.0.0`. Hỗ trợ Mesh vẫn đang thử nghiệm
và nằm ngoài phạm vi bản v1 không dùng mesh.

Tài liệu đầy đủ, chi tiết board được hỗ trợ và hướng dẫn nạp firmware:
[NRSuite Documentation](https://7wp81x.github.io/NRSuite-Docs/)

---

## Bắt đầu nhanh

```bash
pip install platformio
git clone https://github.com/khahdihdz/NRSuite-firmware.git
cd NRSuite-firmware
pio run -e esp32-c3          # build cho board mặc định được khuyên dùng
pio run -e esp32-c3 --target upload   # nạp qua USB
```

Muốn nạp từ điện thoại? Dùng trình nạp có sẵn trong
[app Android NRSuite](https://github.com/7wp81x/nrsuite-android),
xem mục [Nạp firmware](#nạp-firmware).

Bản tiếng Việt, build và nạp bản tiếng Việt:

```bash
pio run -e esp32-c3-vi
pio run -e esp32-c3-vi --target upload
```

## Board được hỗ trợ

| Board | MCU | USB gốc | BLE | BadUSB / MSC | Env |
|---|---|---|---|---|---|
| ESP32-C3 DevKitM-1 | ESP32-C3 | Có (CDC) | Có | Không | `esp32-c3` |
| ESP32-C5 DevKitC-1 (4 MB) | ESP32-C5 | Có (CDC) | Có | Không | `esp32-c5` |
| ESP32-C5 N8R4 (thử nghiệm) | ESP32-C5 | Có (CDC) | Có | Không | `esp32-c5-n8r4` |
| ESP32-C5 N16R4 (thử nghiệm) | ESP32-C5 | Có (CDC) | Có | Không | `esp32-c5-n16r4` |
| ESP32-S3 (fallback an toàn) | ESP32-S3 | Có (TinyUSB) | Có | Có | `esp32-s3` |
| ESP32-S3 N4R2 | ESP32-S3 | Có (TinyUSB) | Có | Có | `esp32-s3-n4r2` |
| ESP32-S3 N4R8 | ESP32-S3 | Có (TinyUSB) | Có | Có | `esp32-s3-n4r8` |
| ESP32-S3 N8R8 | ESP32-S3 | Có (TinyUSB) | Có | Có | `esp32-s3-n8r8` |
| ESP32-S3 N16 | ESP32-S3 | Có (TinyUSB) | Có | Có | `esp32-s3-n16` |
| ESP32-S3 N16R8 | ESP32-S3 | Có (TinyUSB) | Có | Có | `esp32-s3-n16r8` |
| ESP32-S2 Saola-1 | ESP32-S2 | Có (TinyUSB) | Không | Có | `esp32-s2` |
| ESP32 DevKit | ESP32 | Không (cần CP2102/CH340) | Có | Không | `esp32-devkit` |

**Board khuyên dùng để bắt đầu:** ESP32-C3 DevKitM-1. Có USB CDC gốc
(không cần chip USB-UART ngoài), có BLE, và là target build mặc định.

### Cách truyền giao thức

Các target có USB gốc (C3, C5, S2, S3, và C6 khi bật) lắng nghe giao thức
NRSuite trên **cả** cổng USB CDC/JTAG gốc và UART0. Nhờ đó một bản
firmware có thể dùng cho devkit có hai cổng `USB` và `UART` riêng.

ESP32 cổ điển chỉ dùng UART vì không có ngoại vi USB gốc.

`PING`, `STATUS` và heartbeat có trường `transport`, ví dụ:

```json
{ "ok": true, "msg": "pong", "transport": "usb_cdc" }
```

App Android chỉ nên kết nối một cổng vật lý tại một thời điểm. Lệnh được
trả lời trên cổng đã gửi lệnh, sự kiện không đồng bộ đi theo cổng đang
hoạt động gần nhất.

## Tính năng

| Module | Board hỗ trợ | Mô tả |
|---|---|---|
| Quét Wi-Fi | Tất cả (C5: 2.4/5 GHz) | Quét AP với SSID, BSSID, kênh, RSSI, loại bảo mật |
| Bắt gói tin | Tất cả | Bắt pcap ở chế độ monitor, nhảy kênh tự động, lọc EAPOL |
| Deauthentication | Tất cả | Chèn frame deauth 802.11, burst hữu hạn hoặc vòng lặp, thống kê |
| Deauth + bắt gói | Tất cả | Deauth rồi bắt EAPOL ngay để thu handshake WPA |
| WPS Pixie Dust | Tất cả | Luồng WPS registrar M1-M8, bắt Pixie M3, tiếp tục bằng PIN đã khôi phục |
| Phát hiện khóa WPS | Tất cả | Quét thụ động, đọc WPS IE, báo trạng thái AP Setup Locked |
| Phát hiện deauth | Tất cả | Phát hiện thụ động frame deauth/disassoc, sự kiện không đồng bộ |
| Phát hiện client | Tất cả | Phát hiện probe/assoc/reassoc/auth, chế độ chủ động dùng lại deauth |
| Hiện AP ẩn | Tất cả | Phát hiện AP ẩn, ứng viên probe-request, giải mã SSID qua assoc |
| Beacon Spam | Tất cả | Chèn beacon giả, BSSID ngẫu nhiên, hỗ trợ SSID ẩn |
| Captive Portal | C3, C5, S3, ESP32 cổ điển | SoftAP evil twin, server HTTP không đồng bộ, tải HTML tùy chỉnh (tối đa 24 KiB) |
| BLE HID | C3, C5, S3, DevKit | Giả lập bàn phím và chuột Bluetooth, chạy Ducky Script |
| Quét BLE | C3, C5, S3, DevKit | Quét quảng cáo BLE với tên, RSSI, dữ liệu nhà sản xuất, UUID |
| BadUSB | S2, S3 | Chèn HID USB qua TinyUSB, Ducky Script từ bộ nhớ |

## Yêu cầu

### Phần cứng

- Một board trong bảng trên, cáp USB dữ liệu (không phải cáp chỉ sạc).
- Máy tính hoặc điện thoại Android để nạp firmware.

### Phần mềm

- Python 3.11 trở lên, PlatformIO (`pip install platformio`).
- `esptool` nếu nạp thủ công, hoặc app Android NRSuite để nạp từ điện thoại.

## Build

```bash
pip install platformio
pio run -e esp32-c3
pio run                 # build tất cả target release
pio test -e native      # chạy unit test trên máy
```

Build bản tiếng Việt:

```bash
pio run -e esp32-c3-vi
```

Kiểm tra target và phân vùng trước khi build:

```bash
python3 scripts/validate_targets.py
python3 scripts/verify_merged_images.py --environment esp32-c3
```

## Nạp firmware

### Cách A: Nạp từ app Android NRSuite (khuyên dùng)

Dùng trình nạp có sẵn trong app, chọn file `.bin` đã build trong
`release/` cho đúng board.

### Cách B: Nạp qua PlatformIO

```bash
pio run -e esp32-c3 --target upload
```

### Cách C: Nạp thủ công bằng esptool

```bash
esptool.py --port /dev/ttyUSB0 --baud 921600 write_flash 0x0 <file>.bin
```

Thay `/dev/ttyUSB0` bằng cổng đúng trên máy bạn, và `<file>.bin`
bằng file merged cho đúng board trong `release/`.

## Chạy test

```bash
pio test -e native
```

## Cấu trúc dự án

```text
src/                 Code firmware chính (main.cpp, portal, sniffer, ...)
src/lang/            Hệ thống ngôn ngữ: en.h, vi.h, lang.h — thêm cho bản tiếng Việt
boards/              Cấu hình env PlatformIO theo từng board
boards/esp32-c3-vi.ini  Env tiếng Việt cho ESP32-C3
lib/                 Thư viện: BridgeProtocol, DeauthMulti, BLE HID
partitions/          Bảng phân vùng flash theo từng board
scripts/             Kiểm tra target và ảnh merged
portal/portal-vi.html  Mẫu trang portal tiếng Việt (tải lên qua app)
test/                Unit test native
.github/workflows/  CI build tự động và release
```

## Giao thức truyền

Firmware giao tiếp với app Android bằng JSON qua USB serial.
Tên lệnh và khóa JSON **không dịch sang tiếng Việt**, vì app đọc
đúng các chuỗi đó. Ví dụ lệnh `PING` trả về `pong`,
`STATUS` trả về heap, PSRAM, nhiệt độ chip, kích thước flash và SDK.

Chi tiết đầy đủ xem [NRSuite Protocol](https://github.com/7wp81x/NRSuite-Protocol)
và `lib/BridgeProtocol/ProtocolSpec.h`.

## Ngôn ngữ tiếng Việt — cái gì được dịch

Được dịch: chữ trong trang portal mặc định, mẫu trang portal
`portal/portal-vi.html`, README và hướng dẫn này.

Không dịch: tên lệnh/khóa JSON, tên module, tên board, tên env,
log kỹ thuật. Xem chi tiết ở [src/lang/README.md](./src/lang/README.md).

## Đóng góp

Xem [CONTRIBUTING.md](./CONTRIBUTING.md). Bản gốc thuộc về
7wp81x, giấy phép GPL-3.0. Khi đóng góp bản dịch, giữ cùng khóa
chuỗi với `en.h` và không đổi tên lệnh giao thức.

## Repo liên quan

- Firmware gốc: https://github.com/7wp81x/NRSuite-firmware
- App Android: https://github.com/7wp81x/nrsuite-android
- Giao thức: https://github.com/7wp81x/NRSuite-Protocol
- Tài liệu: https://7wp81x.github.io/NRSuite-Docs/

## Bảo mật

Xem [SECURITY.md](./SECURITY.md). Chỉ dùng trên mạng và thiết bị
đã được ủy quyền.

## Giấy phép

GPL-3.0, xem [LICENSE](./LICENSE).

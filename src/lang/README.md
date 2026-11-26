# Hệ thống ngôn ngữ của firmware

Bản gốc 7wp81x/NRSuite-Firmware không có hệ thống ngôn ngữ. Thư mục
`src/lang/` này là phần thêm vào cho bản tiếng Việt, giữ nguyên giao thức.

## File

| File | Nội dung |
|---|---|
| `lang.h` | Chọn ngôn ngữ lúc biên dịch. Định nghĩa `FIRMWARE_LANG_VI` thì dùng `vi.h`, không thì dùng `en.h`. |
| `en.h` | Chuỗi tiếng Anh gốc, chỉ gồm chuỗi hiển thị cho người dùng trong portal. |
| `vi.h` | Bản dịch tiếng Việt, cùng khóa, cùng thứ tự với `en.h`. |

## Bật tiếng Việt

```bash
pio run -e esp32-c3-vi
pio run -e esp32-c3-vi --target upload
```

Env `esp32-c3-vi` nằm ở `boards/esp32-c3-vi.ini`, là bản sao của
`esp32-c3` cộng thêm `-DFIRMWARE_LANG_VI=1`. Các board khác muốn dùng
tiếng Việt thì thêm cờ đó vào `build_flags` của env tương ứng.

## Cái gì được dịch, cái gì không

Được dịch: chữ trong trang portal mặc định (`Đang kết nối...`,
tiêu đề và nội dung trang thông báo, nút `Tiếp tục`), và mẫu trang
portal tiếng Việt ở `portal/portal-vi.html`.

Không dịch, vì app Android đọc đúng các chuỗi này:

- Tên lệnh và khóa JSON qua USB serial: `PING`, `STATUS`, `DEAUTH`,
  `START_PORTAL`, `pong`, `transport`, `ok`, `msg`, ...
- Tên module, tên board, tên env PlatformIO.
- Log kỹ thuật.

## Trang portal tiếng Việt

Trang portal thật không nằm cứng trong firmware, mà do app Android
tải lên (tối đa 24 KiB). Mẫu tiếng Việt ở `portal/portal-vi.html`
là file để tải lên theo cách đó, không phải trang mặc định của firmware.

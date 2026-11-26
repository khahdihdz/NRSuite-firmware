// Ngon ngu hien thi cua firmware NRSuite — them boi ban tieng Viet.
// Goc: 7wp81x/NRSuite-Firmware, GPL-3.0, FW 1.0.0, commit e7f07d3.
// Repo goc KHONG co he thong i18n: chuoi tieng Anh nam rac trong src/
// va trang portal mac dinh chi co "<p>Connecting...</p>".
// File nay tach cac chuoi HIEN THI CHO NGUOI DUNG (portal, thong bao)
// ra khoi code, de dich ma khong doi giao thuc.
//
// KHONG dich:
//  - Ten lenh JSON / khoa JSON tren USB serial: PING, STATUS, DEAUTH,
//    START_PORTAL, "pong", "transport", ... — app Android doc cac khoa nay.
//  - Ten module, ten board, ten env PlatformIO.
//  - Log ky thuat trong NrDebugLog.h.
//
// Cach bat tieng Viet:
//   pio run -e esp32-c3-vi
// Env nay (boards/esp32-c3-vi.ini) dinh nghia FIRMWARE_LANG_VI=1.
// Mac dinh (khong dinh nghia) la tieng Anh, giu nguyen hanh vi goc.
#pragma once

#if defined(FIRMWARE_LANG_VI)
#include "vi.h"
#else
#include "en.h"
#endif

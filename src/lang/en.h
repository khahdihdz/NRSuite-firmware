// English strings — goc, giu nguyen van ban cua 7wp81x/NRSuite-Firmware.
// Chi gom cac chuoi hien thi cho nguoi dung trong portal.
// Cac chuoi giao thuc JSON (PING/STATUS/DEAUTH/...) khong nam o day.
#pragma once

namespace nrsuite {
namespace lang {

inline constexpr const char* kLangCode = "en";
inline constexpr const char* kLangName = "English";

// Portal loading placeholder (src/portal.cpp, loadingPlaceholder()).
inline constexpr const char* kConnecting = "Connecting...";

// Portal notice page (src/portal.cpp, noticePage()).
inline constexpr const char* kSecurityTestTitle = "Security Awareness Test";
inline constexpr const char* kSecurityTestBody1 =
    "You connected to a Wi-Fi network set up as part of an authorized security "
    "assessment. No credentials or personal data are stored by this test.";
inline constexpr const char* kSecurityTestBody2 =
    "In a real attack, a network like this could be used to intercept your traffic "
    "or steal login credentials. Always verify network names before connecting.";
inline constexpr const char* kContinue = "Continue";

// Nhan log hien thi, khong phai khoa giao thuc. Chi dung de dich thong bao
// cho nguoi doc log; phan hoi JSON cho app Android van giu tieng Anh.
inline constexpr const char* kArmedOk = "Armed successfully";
inline constexpr const char* kArmFailed = "failed to arm";
inline constexpr const char* kHidNotSupported = "HID not supported on this chip";

}  // namespace lang
}  // namespace nrsuite

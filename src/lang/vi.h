// Chuoi tieng Viet — dich tu en.h, cung khoa, cung thu tu.
// File nay la UTF-8. Trang portal phai co <meta charset="utf-8"> (da co
// trong portal/portal-vi.html va trong noticePage() cua portal.cpp).
// Chi dich chuoi hien thi cho nguoi dung; KHONG dich ten lenh JSON,
// khoa JSON, ten module, ten board, ten env PlatformIO.
#pragma once

namespace nrsuite {
namespace lang {

inline constexpr const char* kLangCode = "vi";
inline constexpr const char* kLangName = "Tiếng Việt";

// Trang portal dang tai (src/portal.cpp, loadingPlaceholder()).
inline constexpr const char* kConnecting = "Đang kết nối...";

// Trang thong bao cua portal (src/portal.cpp, noticePage()).
inline constexpr const char* kSecurityTestTitle = "Kiểm tra nhận thức bảo mật";
inline constexpr const char* kSecurityTestBody1 =
    "Bạn đã kết nối vào một mạng Wi-Fi được dựng lên trong khuôn khổ một đợt "
    "đánh giá bảo mật đã được ủy quyền. Bài kiểm tra này không lưu mật khẩu "
    "hay dữ liệu cá nhân của bạn.";
inline constexpr const char* kSecurityTestBody2 =
    "Trong một cuộc tấn công thật, một mạng như thế này có thể bị dùng để chặn "
    "lưu lượng của bạn hoặc đánh cắp thông tin đăng nhập. Hãy luôn kiểm tra "
    "tên mạng trước khi kết nối.";
inline constexpr const char* kContinue = "Tiếp tục";

// Nhan log hien thi, khong phai khoa giao thuc.
inline constexpr const char* kArmedOk = "Đã kích hoạt thành công";
inline constexpr const char* kArmFailed = "kích hoạt thất bại";
inline constexpr const char* kHidNotSupported = "Chip này không hỗ trợ HID";

}  // namespace lang
}  // namespace nrsuite

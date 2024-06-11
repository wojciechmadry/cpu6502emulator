#include "gui_utils.hpp"

namespace utils {

QString toHex(std::uint32_t val) {
  return QString("0x") + QString::number(val, 16).toUpper();
}

std::optional<std::uint32_t> toUint32BaseX(const QString &qstr, int base) {
  bool isOk;
  auto converted = qstr.toUInt(&isOk, base);
  if (isOk) {
    return converted;
  }
  return {};
}

std::optional<std::uint32_t> toUint32Base10(const QString &qstr) {
  return toUint32BaseX(qstr, 10);
}

std::optional<std::uint32_t> toUint32Base16(const QString &qstr) {
  return toUint32BaseX(qstr, 16);
}

std::optional<std::uint32_t> toUint32(const QString &qstr) {
  auto converted = toUint32Base10(qstr);
  if (converted.has_value()) {
    return converted;
  }
  converted = toUint32Base16(qstr);
  if (converted.has_value()) {
    return converted;
  }
  return {};
}

} // namespace utils

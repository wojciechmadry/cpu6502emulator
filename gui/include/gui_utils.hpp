#ifndef CPU6502_GUI_UTILS_HPP
#define CPU6502_GUI_UTILS_HPP

#include <QString>
#include <cstdint>
#include <functional>
#include <optional>
#include <qgroupbox.h>

namespace constant {
static constexpr auto true_str = "true";
static constexpr auto false_str = "false";
} // namespace constant

enum class BaseSystem { Decimal, Hex };

namespace utils {
QString toHex(std::uint32_t val);

// Convert to Uint32 value can be also decimal and hexdecimal
std::optional<std::uint32_t> toUint32(const QString &qstr);

std::optional<std::uint32_t> toUint32Base10(const QString &qstr);

std::optional<std::uint32_t> toUint32Base16(const QString &qstr);

std::optional<std::uint32_t> toUint32BaseX(const QString &qstr, int base);

template <typename ClassToFind>
std::optional<std::reference_wrapper<ClassToFind>>
searchGroupBox(QGroupBox *groupBox) {
  if (groupBox == nullptr) {
    return {};
  }
  auto allChildrens = groupBox->children();
  for (auto child : allChildrens) {
    auto classFound = dynamic_cast<ClassToFind *>(child);
    if (classFound) {
      return *classFound;
    }
  }
  return {};
}
} // namespace utils

#endif // CPU6502_GUI_UTILS_HPP

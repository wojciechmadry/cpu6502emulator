#ifndef CPU6502_GUI_UTILS_HPP
#define CPU6502_GUI_UTILS_HPP

#include <QString>
#include <cstdint>
#include <optional>

namespace constant {
static constexpr auto true_str = "true";
static constexpr auto false_str = "false";
}

namespace utils{
    QString toHex(std::uint32_t val);

    std::optional<std::uint32_t> toUint32(const QString& qstr);
}

#endif  // CPU6502_GUI_UTILS_HPP

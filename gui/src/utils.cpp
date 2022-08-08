#include "utils.hpp"

namespace utils {

QString toHex(std::uint32_t val)
{
    return QString("0x") + QString::number(val, 16).toUpper();
}

std::optional<std::uint32_t> toUint32(const QString& qstr)
{
    bool isOk;
    auto converted = qstr.toUInt(&isOk, 10);
    if (isOk)
    {
        return converted;
    }
    converted = qstr.toUInt(&isOk, 16);
    if (isOk)
    {
        return converted;
    }
    return {};
}

}
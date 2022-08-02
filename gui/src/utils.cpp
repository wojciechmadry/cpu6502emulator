#include "utils.hpp"

namespace utils {

QString toHex(std::uint32_t val)
{
    return QString("0x") + QString::number(val, 16).toUpper();
}



}
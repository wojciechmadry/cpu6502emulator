#include "cpu_except.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace cpu6502::exceptions {

infinite_loop::infinite_loop(const std::int64_t last_instruction) noexcept {
  m_err_msg = "Cycles counter don't change, propably infinity loop, last "
              "called instruction : ";
  m_err_msg += to_hex(last_instruction);
}
const char *infinite_loop::what() const noexcept { return m_err_msg.c_str(); }

bad_instruction::bad_instruction(const std::int64_t instruction) noexcept {
  m_err_msg = "Function : " + to_hex(instruction) + " doesn't exist.";
}

const char *bad_instruction::what() const noexcept { return m_err_msg.c_str(); }

std::string to_hex(const std::int64_t ins) noexcept {
  std::stringstream stream;
  stream << std::hex << ins;
  auto str = stream.str();
  std::transform(std::begin(str), std::end(str), std::begin(str),
                 [](auto a_char) { return std::toupper(a_char); });
  return std::string("0x") + str;
}

} // namespace cpu6502::exceptions

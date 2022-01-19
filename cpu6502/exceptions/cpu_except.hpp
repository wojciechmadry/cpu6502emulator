#ifndef CPU_EXCEPT_HPP
#define CPU_EXCEPT_HPP

#include <exception>
#include <stdexcept>
#include <cstdint>
#include <string>

namespace cpu6502::exceptions{

std::string to_hex(const std::int64_t ins) noexcept;

class infinite_loop : public std::exception
{
    std::string m_err_msg;
    public:
    infinite_loop(const std::int64_t last_instruction) noexcept;
    const char * what () const noexcept override;
};


class bad_instruction : public std::exception
{
    std::string m_err_msg;
    public:
    bad_instruction(const std::int64_t instruction) noexcept;
    const char * what () const noexcept override;
};

}

#endif  // CPU_EXCEPT_HPP

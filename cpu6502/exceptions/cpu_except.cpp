#include "cpu_except.hpp"


namespace cpu6502::exceptions{

infinite_loop::infinite_loop(const std::int64_t last_instruction) noexcept
{
    m_err_msg = "Cycles counter don't change, propably infinity loop, last called instruction : ";
    m_err_msg += std::to_string(last_instruction);
}
const char * infinite_loop::what () const noexcept
{
    return m_err_msg.c_str();
}

bad_instruction::bad_instruction(const std::int64_t instruction) noexcept
{
    m_err_msg = "Function : " + std::to_string(instruction) + " doesn't exist.";
}

const char * bad_instruction::what () const noexcept
{
    return m_err_msg.c_str();
}

}
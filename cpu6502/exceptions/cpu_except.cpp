#include "cpu_except.hpp"


namespace cpu6502::exceptions{

const char * infinite_loop::what () const noexcept
{
    return "Cycles counter don't change, propably infinity loop.";
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
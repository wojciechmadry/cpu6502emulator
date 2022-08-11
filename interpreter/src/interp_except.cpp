#include "interp_except.hpp"

namespace cpu6502::interpreter::exceptions{

empty_instruction::empty_instruction() noexcept
{
}

const char * empty_instruction::what () const noexcept
{
    return "Empty instruction";
}

bad_instruction_size::bad_instruction_size() noexcept
{
}

const char * bad_instruction_size::what () const noexcept
{
    return "Bad instruction name size";
}

bad_addressing_mode::bad_addressing_mode() noexcept
{
}

const char * bad_addressing_mode::what () const noexcept
{
    return "Cant match any addressing mode";
}

bad_label_value::bad_label_value() noexcept
{
}

const char * bad_label_value::what () const noexcept
{
    return "Label value is not a number";
}

} // ns cpu6502::interpreter::exceptions

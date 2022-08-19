#include "interpreter.hpp"

namespace cpu6502::interpreter
{

void Interpreter::set_states_to_remember(std::uint32_t state_to_remember) noexcept
{
    m_debug_state_to_remember = state_to_remember;
}

std::uint32_t Interpreter::get_current_state() const noexcept
{
    return m_debug_actual_state;
}

}

#include "interpreter.hpp"

namespace cpu6502::interpreter
{

const std::vector<Interpreter::INTERPRETER_CLONE_TYPE>& Interpreter::get_debug_states() const noexcept
{
    return this->m_debug_states;
}

void Interpreter::debug_go_right()
{
    this->load_state(m_debug_actual_state + 1);
}

void Interpreter::debug_go_left()
{
    this->load_state(m_debug_actual_state - 1);
}

// TODO: Simplify and optimize this
void Interpreter::insert_new_state()
{
    if (m_debug_state_to_remember == 0)
    {
        return;
    }
    
    // 3 possible states
    // 1. X (Empty vector)
    // 2. ......X (You are in the beginning)
    // 3. ...X... (You are in mid or something similar)

    // First and Second state
    if(m_debug_actual_state == m_debug_states.size())
    {
        ++m_debug_actual_state;
        m_debug_states.emplace_back(this->clone());
    }
    else // Third state we need also remove all next states
    {
        while(m_debug_actual_state > m_debug_states.size())
        {
            m_debug_states.pop_back();
        }
        m_debug_states.emplace_back(this->clone());
        ++m_debug_actual_state;
    }

    // We need remove first states
    if (m_debug_states.size() > m_debug_state_to_remember)
    {
        const auto element_to_erase = m_debug_states.size() - m_debug_state_to_remember;
        m_debug_states.erase(m_debug_states.begin(), m_debug_states.begin() + static_cast<long>(element_to_erase));
    }
}

void Interpreter::load_state(std::uint32_t state_number)
{
    if (state_number >= m_debug_states.size() || state_number >= m_debug_state_to_remember)
    {
        return;
    }
    m_debug_actual_state = state_number;
    const auto& state = m_debug_states[state_number];
    m_labels = state.first;
    auto& cpu = m_cpu.get();
    auto& reg = cpu.get_registers();
    auto& mem = cpu.get_memory();
    mem = *state.second.second;
    reg = state.second.first->get_registers();
}

void Interpreter::set_states_to_remember(std::uint32_t state_to_remember) noexcept
{
    m_debug_state_to_remember = state_to_remember;
}

std::uint32_t Interpreter::get_current_state() const noexcept
{
    return m_debug_actual_state;
}

}

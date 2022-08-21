#include "interpreter.hpp"

#include <fmt/core.h> // TODO: Delete this

namespace cpu6502::interpreter
{

std::uint32_t Interpreter::get_states_to_remember() const noexcept
{
    return m_debug_state_to_remember;
}

const std::list<Interpreter::INTERPRETER_CLONE_TYPE>& Interpreter::get_debug_states() const noexcept
{
    return this->m_debug_states;
}

void Interpreter::debug_go_right()
{
    auto it_copy = m_debug_actual_state;
    ++it_copy;
    if (it_copy == m_debug_states.end())
    {
        this->load_state(m_debug_actual_state);
    }
    else
    {
        this->load_state(++m_debug_actual_state);
    }
}

void Interpreter::debug_go_left()
{
    if (m_debug_actual_state == m_debug_states.begin())
    {
        this->load_state(m_debug_actual_state);
    }
    else
    {
        this->load_state(--m_debug_actual_state);
    }
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
    if(m_debug_actual_state == --m_debug_states.end())
    {
        m_debug_states.emplace_back(this->clone());
        m_debug_actual_state = --m_debug_states.end();
    }
    else // Third state we need also remove all next states
    {
        while(--m_debug_states.end() != m_debug_actual_state)
        {
            m_debug_states.pop_back();
        }
        m_debug_states.emplace_back(this->clone());
        m_debug_actual_state = --m_debug_states.end();
    }

    // We need remove first states
    if (m_debug_states.size() > m_debug_state_to_remember)
    {
        const auto element_to_erase = m_debug_states.size() - m_debug_state_to_remember;
        //fmt::print("Vec size: {} | Delete n: {}\n", m_debug_states.size(), element_to_erase);
        for(std::decay_t<decltype(element_to_erase)> i = 0u ; i < element_to_erase ; ++i)
        {
            m_debug_states.pop_front();
        }
        m_debug_actual_state = --m_debug_states.end();
        
        //m_debug_states.erase(m_debug_states.begin(), m_debug_states.begin() + static_cast<long>(element_to_erase));
    }
}

void Interpreter::load_state(std::list<INTERPRETER_CLONE_TYPE>::iterator it_state)
{
    if (it_state == m_debug_states.end())
    {
        return;
    }
    m_labels = it_state->first;
    auto& cpu = m_cpu.get();
    auto& reg = cpu.get_registers();
    auto& mem = cpu.get_memory();
    mem = *it_state->second.second;
    reg = it_state->second.first->get_registers();
}

void Interpreter::set_states_to_remember(std::uint32_t state_to_remember) noexcept
{
    m_debug_state_to_remember = state_to_remember;
}

std::optional<std::list<Interpreter::INTERPRETER_CLONE_TYPE>::iterator> Interpreter::get_current_state() const noexcept
{
    if (m_debug_actual_state != m_debug_states.end())
    {
        return m_debug_actual_state;
    }
    return {};
}

}

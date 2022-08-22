#include "interpreter.hpp"

namespace cpu6502::interpreter
{

std::uint32_t Interpreter::get_current_state_pose() const noexcept
{
    std::uint32_t cur_pose = 0u;
    for(auto it_begin = m_debug_states.begin() ; it_begin != m_debug_actual_state ; ++it_begin)
    {
        ++cur_pose;
    }
    return cur_pose;
}

std::uint32_t Interpreter::get_states_to_remember() const noexcept
{
    return m_debug_state_to_remember;
}

const std::list<Interpreter::INTERPRETER_CLONE_TYPE>& Interpreter::get_debug_states() const noexcept
{
    return this->m_debug_states;
}

void Interpreter::debug_mode_change_command(utils::DebugModeNextCommand next_command)
{
    if (next_command == utils::DebugModeNextCommand::GoLeft)
    {
        this->debug_go_left();
    }
    else if (next_command == utils::DebugModeNextCommand::GoRight)
    {
        this->debug_go_right();
    }
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

void Interpreter::insert_new_state()
{
    if (m_debug_state_to_remember == 0)
    {
        return;
    }

    while(--m_debug_states.end() != m_debug_actual_state)
    {
        m_debug_states.pop_back();
    }

    m_debug_states.emplace_back(this->clone());

    while(m_debug_states.size() > m_debug_state_to_remember)
    {
        m_debug_states.pop_front();
    }
    
    m_debug_actual_state = --m_debug_states.end();
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
    const auto old_size = m_debug_state_to_remember;
    m_debug_state_to_remember = state_to_remember;
    if (old_size > m_debug_state_to_remember)
    {
        while(m_debug_states.size() > m_debug_state_to_remember)
        {
            m_debug_states.pop_front();
        }
        if (m_debug_states.empty())
        {
            m_debug_actual_state = m_debug_states.end();
        }
        else
        {
            m_debug_actual_state = --m_debug_states.end();
        }
        this->load_state(m_debug_actual_state);
    }
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

#include "gui_manager.hpp"
#include "memory.hpp"

GuiManager::GuiManager(cpu6502::CPU& cpu, cpu6502::interpreter::Interpreter& interpreter, cpu6502::Memory& memory) noexcept
: m_cpu(cpu), m_interpreter(interpreter), m_memory(memory)
{
    
}


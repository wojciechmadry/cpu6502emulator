#include "interpreter.hpp"
#include "utility.hpp"
#include "interp_except.hpp"

#include <fmt/core.h>
#include <cctype>

namespace cpu6502::interpreter
{
Interpreter::Interpreter(Interpreter& other) noexcept : m_cpu(other.m_cpu), m_labels(other.m_labels)
{

}

Interpreter::Interpreter(cpu6502::CPU& cpu) noexcept : m_cpu(cpu)
{

}

cpu6502::CPU& Interpreter::get_cpu() noexcept
{
    return m_cpu;
}

const cpu6502::CPU& Interpreter::get_cpu() const noexcept
{
    return m_cpu;
}

void Interpreter::add_label(std::string label_name, const std::uint32_t address) noexcept
{
    for(auto& ch : label_name)
    {
        ch = static_cast<char>(std::toupper(static_cast<int>(ch)));
    }
    m_labels[label_name] = address;
}

Addressing Interpreter::interprete(std::string_view line)
{
    if (line.empty())
    {
        throw exceptions::empty_instruction{};
    }

    if (line.size() < 3)
    {
        throw exceptions::bad_instruction_size{};
    }

    const auto instruction_info = cpu6502::interpreter::utils::get_instruction(line.substr(0, 3));
    const auto address_type = load_instruction(line.substr(3), instruction_info);
    m_cpu.get().execute(std::numeric_limits<u32>::max());

    return address_type;
}

} // namespace cpu6502
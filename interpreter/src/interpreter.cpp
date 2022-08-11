#include "interpreter.hpp"
#include "instruction.hpp"
#include "utility.hpp"
#include "interp_except.hpp"
#include <cctype>
#include <exception>
#include <limits>
#include <optional>

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

const std::unordered_map<std::string, std::uint32_t>& Interpreter::get_labels() const noexcept
{
    return m_labels;
}

void Interpreter::clear_labels() noexcept
{
    m_labels.clear();
}

Addressing Interpreter::interprete(std::string_view line)
{
    if (line.empty())
    {
        throw exceptions::empty_instruction{};
    }

    // This is comment
    if (line[0] == '#')
    {
        return Addressing::Comment;
    }

    // Create label TODO: This should be different function (is too complex)
    const auto foundCreateLabel = line.find(":=");
    if (foundCreateLabel != std::string::npos)
    {
        const auto asString = std::string{line};
        const auto StrValue = asString.substr(foundCreateLabel + 2);
        bool containsLetters = false;
        std::optional<std::uint32_t> address;

        for(auto c : StrValue)
        {
            if (c > '9' || c < '0')
            {
                containsLetters = true;
                break;
            }
        }
        if (containsLetters)
        {
            try 
            {
                address = static_cast<std::uint32_t>(std::stoul(StrValue, nullptr, 16));
            }
            catch(const std::exception&) { }
        }
        else
        {
            try 
            {
                address = static_cast<std::uint32_t>(std::stoul(StrValue, nullptr, 10));
            }
            catch(const std::exception&) { }
        }
        
        if (address.has_value())
        {
            this->add_label(asString.substr(0, foundCreateLabel), *address);
        }
        else
        {
            throw exceptions::bad_label_value{};
        }

        return Addressing::CreateLabel;
    }

    // Check if command is correct and execute it
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
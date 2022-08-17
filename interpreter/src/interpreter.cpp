#include "interpreter.hpp"
#include "instruction.hpp"
#include "utility.hpp"
#include "interp_except.hpp"
#include <cctype>
#include <exception>
#include <limits>
#include <optional>
#include <stdexcept>
#include <fstream>

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

void Interpreter::add_label(std::string label_name, const std::uint32_t address)
{
    if (label_name.empty())
    {
        throw std::out_of_range("The label name can't be empty");
    }
    for(auto& ch : label_name)
    {
        ch = static_cast<char>(std::toupper(static_cast<int>(ch)));
        const auto isLetter = ch >= 'A' && ch <= 'Z';
        const auto isUnderscore = ch == '_';
        const auto isNumber = ch >= '0' && ch <= '9';
        if (!isLetter && !isUnderscore && !isNumber)
        {
            throw std::out_of_range("The label name must consist of letters only");
        }
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
    if (this->is_comment(line))
    {
        return Addressing::Comment;
    }

    const auto isLabel = create_label_instruction(line);
    if (isLabel)
    {
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

bool Interpreter::is_comment(std::string_view line) const noexcept
{
    auto has_only_spaces = [=]()
    {
        for(auto ch : line)
        {
            if (ch != ' ')
            {
                return false;
            }
        }
        return true;
    };

    if (line.empty() || line[0] == '#' || has_only_spaces())
    {
        return true;
    }
    return false;
}

bool Interpreter::create_label_instruction(std::string_view command)
{
    const auto foundCreateLabel = command.find(":");
    if (foundCreateLabel == std::string::npos)
    {
        return false;
    }

    const auto foundEqual = command.find("=");

    if (foundEqual != std::string::npos)
    {
        const auto asString = std::string{command};
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
    }
    else
    {
        const auto asString = std::string{command};
        auto labelName = asString.substr(0, foundCreateLabel);
        if(foundCreateLabel + 1 != asString.size())
        {
            throw std::out_of_range("'LABELNAME:' cant have any letter after ':'");
        }

        this->add_label(std::move(labelName), m_cpu.get().get_registers().PC.get());
    }

    return true;
}

// Load .asm file
void Interpreter::load_asm(const std::string& filename) noexcept
{
    m_asm_commands.clear();
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if(!(file.good() && file.is_open()))
    {
        return;
    }
    std::string line;

    while(std::getline(file, line))
    {
        if(this->is_comment(line))
        {
            continue;
        }
        bool isLabel = false;
        try {
            const auto foundLabel = line.find(":=");
            if (foundLabel != std::string::npos)
            {
                isLabel = create_label_instruction(line);
            }
        } catch (const std::exception&) {
        }
        
        if (isLabel)
        {
            continue;
        }
        m_asm_commands.emplace_back(std::move(line));
    }

    file.close();
}

// Execute previously loaded .asm file
void Interpreter::execute_asm()
{
    if (m_asm_commands.empty())
    {
        return;
    }

    for(const auto& command : m_asm_commands)
    {
        this->interprete(command);
    }

    m_asm_commands.clear();
}

std::vector<std::string>& Interpreter::get_commands()
{
    return m_asm_commands;
}

const std::vector<std::string>& Interpreter::get_commands() const
{
    return m_asm_commands;
}

} // namespace cpu6502
#include "instruction.hpp"

namespace cpu6502::interpreter{

std::string_view address_enum_to_str(const Addressing addressing_mode)
{
    switch(addressing_mode)
    {
        case Addressing::Absolute:
        {
            return "Absolute";
            break;
        }
        case Addressing::AbsoluteX:
        {
            return "AbsoluteX";
            break;
        }
        case Addressing::AbsoluteY:
        {
            return "AbsoluteY";
            break;
        }
        case Addressing::Accumulator:
        {
            return "Accumulator";
            break;
        }
        case Addressing::BAD_ADDRESING_MODE:
        {
            return "BadAddresingMode";
            break;
        }
        case Addressing::Immediate:
        {
            return "Immediate";
            break;
        }
        case Addressing::Implicit:
        {
            return "Implicit";
            break;
        }
        case Addressing::Indirect:
        {
            return "Indirect";
            break;
        }
        case Addressing::IndirectX:
        {
            return "IndirectX";
            break;
        }
        case Addressing::IndirectY:
        {
            return "IndirectY";
            break;
        }
        case Addressing::NUM_OF_ADDRESSING:
        {
            return "NumOfAddressing";
            break;
        }
        case Addressing::Relative:
        {
            return "Relative";
            break;
        }
        case Addressing::ZeroPage:
        {
            return "ZeroPage";
            break;
        }
        case Addressing::ZeroPageX:
        {
            return "ZeroPageX";
            break;
        }
        case Addressing::ZeroPageY:
        {
            return "ZeroPageY";
            break;
        }
        default:
        {
            return "Unknown";
            break;
        }
    }
}

const std::string& InstructionInfo::get_instruction_name() const noexcept
{
    return m_instruction_name;
}

std::string& InstructionInfo::get_instruction_name() noexcept
{
    return m_instruction_name;
}

const std::vector<InstructionInfo::SmallAddressInfo>& InstructionInfo::get_addressing_vector() const noexcept
{
    return m_possible_addressing_mode;
}

void InstructionInfo::add_address(const SmallAddressInfo sAi) noexcept
{
    m_possible_addressing_mode.emplace_back(sAi);
}

int InstructionInfo::SmallAddressInfo::get_op_code() const noexcept
{
    return m_op;
}

Addressing InstructionInfo::SmallAddressInfo::get_mode() const noexcept
{
    return m_mode;
}

void InstructionInfo::SmallAddressInfo::set_op_code(int op) noexcept
{
    m_op = op;
}

void InstructionInfo::SmallAddressInfo::set_mode(Addressing mode) noexcept
{
    m_mode = mode;
}

AVL_type AddressInfo::get_avl() const noexcept
{
    return m_type;
}

void AddressInfo::set_avl(AVL_type type) noexcept
{
    m_type = type;
}


ADDITIONAL_info AddressInfo::get_additional_info() const noexcept
{
    return m_info;
}
    
void AddressInfo::set_additional_info(ADDITIONAL_info info) noexcept
{
    m_info = info;
}

const std::string& AddressInfo::get_value() const noexcept
{
    return m_value;
}

void AddressInfo::set_value(std::string value) noexcept
{
    m_value = std::move(value);
}

Addressing AddressInfo::get_mode() const noexcept
{
    return m_mode;
}

void AddressInfo::set_mode(Addressing mode) noexcept
{
    m_mode = mode;
}

VALUE_TYPE AddressInfo::get_value_type() const noexcept
{
    return m_value_type;
}

void AddressInfo::set_value_type(const VALUE_TYPE value_type) noexcept
{
    m_value_type = value_type;
}

std::uint32_t AddressInfo::get_val_as_uint32() const
{
    return static_cast<std::uint32_t>(std::stoul(m_value, nullptr, static_cast<int>(m_value_type)));    
}

AddressInfo AddressInfo::create_address(Addressing mode, AVL_type avl, std::string_view value,
                                                 VALUE_TYPE value_type) noexcept
{
    AddressInfo ai;
    ai.set_mode(mode);
    ai.set_avl(avl);
    ai.set_value(std::string{value});
    ai.set_value_type(value_type);
    return ai;
}


} // namespace interpreter

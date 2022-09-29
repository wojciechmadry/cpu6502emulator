#include <fmt/core.h>  // remove this
#include <limits>
#include "instruction.hpp"
#include "interpreter.hpp"
#include "interp_utils.hpp"
#include "interp_except.hpp"

namespace cpu6502::interpreter
{

Addressing Interpreter::load_instruction(std::string_view address, const InstructionInfo& info)
{    

    auto to_upper = [](std::string val)
    {
        for(auto& ch : val)
        {
            ch = static_cast<char>(std::toupper(static_cast<int>(ch)));
        }
        return val;
    };

    const auto& possible_addresing = info.get_addressing_vector();

    const auto addressing_info = utils::get_address_info(address, possible_addresing);

    Addressing matched = Addressing::BAD_ADDRESING_MODE;

    // Processor
    auto& cpu = m_cpu.get();
    // Processor memory
    auto& memory = cpu.get_memory();
    // Program counter
    auto& PC = cpu.get_registers().PC;
    // CPU register
    auto& reg = cpu.get_registers();
    
    for(const auto& addressing: possible_addresing)
    {
        const auto op_code_val = addressing.get_op_code();
        
        switch(addressing.get_mode())
        {
            case Addressing::Implicit:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::Implicit)
                    {
                        matched = Addressing::Implicit;
                        memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                    }
                }
                break;
            }
            case Addressing::Accumulator:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::Accumulator)
                    {
                        matched = Addressing::Accumulator;
                        memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                    }
                }
                break;
            }
            case Addressing::Immediate:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::Immediate)
                    {
                        std::uint8_t value;
                        const auto avl = ai.get_avl();
                        if(avl == AVL_type::value)
                        {
                            try
                            {
                                const auto uival = ai.get_val_as_uint32();
                                value = static_cast<std::uint8_t>(uival);
                                matched = Addressing::Immediate;
                            }
                            catch(const std::exception&)
                            {
                            }
                            
                        }
                        else if(avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(ai.get_value()));
                            if(find_label != m_labels.end())
                            {
                                matched = Addressing::Immediate;
                                const auto label_value = find_label->second;
                                if(ai.get_additional_info() == ADDITIONAL_info::HI)
                                {
                                    value = static_cast<std::uint8_t>((label_value & 0xFF00) >> 8);
                                }
                                else if (ai.get_additional_info() == ADDITIONAL_info::LO)
                                {
                                    value = static_cast<std::uint8_t>(label_value & 0xFF);
                                }
                                else
                                {
                                    matched = Addressing::BAD_ADDRESING_MODE;
                                }
                            }
                        }

                        if(matched != Addressing::BAD_ADDRESING_MODE)
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = value;
                        }

                        break;
                    }
                }
                
                break;
            }
            case Addressing::ZeroPage:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::ZeroPage)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();

                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                if(iaddr <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::ZeroPage;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if (avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                const auto label_value = find_label->second;
                                if(label_value <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    matched = Addressing::ZeroPage;
                                    addr = find_label->second;
                                }
                            }
                        }

                        if(addr != std::numeric_limits<uint32_t>::max()) 
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = static_cast<std::uint8_t>(addr);
                        }
                    }
                }
                break;
            }
            case Addressing::ZeroPageX:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::ZeroPageX)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();

                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                if(iaddr + static_cast<std::uint32_t>(reg.IRX.get()) <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::ZeroPageX;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if (avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                auto label_value = find_label->second;
                                if(label_value + static_cast<std::uint32_t>(reg.IRX.get()) <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    matched = Addressing::ZeroPageX;
                                    addr = label_value;
                                }
                            }
                        }

                        if(addr != std::numeric_limits<std::uint32_t>::max())
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = static_cast<std::uint8_t>(addr);
                        }
                    }
                }
                break;
            }
            case Addressing::ZeroPageY:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::ZeroPageY)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();

                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                if(iaddr + static_cast<std::uint32_t>(reg.IRY.get()) <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::ZeroPageY;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if (avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                auto label_value = find_label->second;
                                if(label_value + static_cast<std::uint32_t>(reg.IRY.get()) <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    matched = Addressing::ZeroPageY;
                                    addr = label_value;
                                }
                            }
                        }

                        if(addr != std::numeric_limits<std::uint32_t>::max())
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = static_cast<std::uint8_t>(addr);
                        }
                    }
                }
                break;
            }
            case Addressing::Absolute:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::Absolute)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();

                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                if(iaddr < std::numeric_limits<std::uint16_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::Absolute;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if (avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                const auto label_value = find_label->second;
                                if(label_value < std::numeric_limits<std::uint16_t>::max())
                                {
                                    matched = Addressing::Absolute;
                                    addr = find_label->second;
                                }
                            }
                        }

                        if(addr != std::numeric_limits<uint32_t>::max()) 
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = static_cast<std::uint8_t>(addr);
                            memory[PC.get() + 2u] = static_cast<std::uint8_t>(addr >> 8);
                        }
                    }
                }
                break;
            }
            case Addressing::AbsoluteX:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::AbsoluteX)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();

                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                const auto add_irx_offset = iaddr + static_cast<std::uint32_t>(reg.IRX.get());
                                if(add_irx_offset < std::numeric_limits<std::uint16_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::AbsoluteX;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if (avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                auto label_value = find_label->second;
                                const auto add_irx_offset = label_value + static_cast<std::uint32_t>(reg.IRX.get());

                                if(add_irx_offset < std::numeric_limits<std::uint16_t>::max())
                                {
                                    matched = Addressing::AbsoluteX;
                                    addr = label_value;
                                }
                            }
                        }

                        if(addr != std::numeric_limits<std::uint32_t>::max())
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = static_cast<std::uint8_t>(addr);
                            memory[PC.get() + 2u] = static_cast<std::uint8_t>(addr >> 8);
                        }
                    }
                }
                break;
            }
            case Addressing::AbsoluteY:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::AbsoluteY)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();

                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                const auto add_iry_offset = iaddr + static_cast<std::uint32_t>(reg.IRY.get());
                                if(add_iry_offset < std::numeric_limits<std::uint16_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::AbsoluteY;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if (avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                auto label_value = find_label->second;
                                const auto add_iry_offset = label_value + static_cast<std::uint32_t>(reg.IRY.get());

                                if(add_iry_offset < std::numeric_limits<std::uint16_t>::max())
                                {
                                    matched = Addressing::AbsoluteY;
                                    addr = label_value;
                                }
                            }
                        }

                        if(addr != std::numeric_limits<std::uint32_t>::max())
                        {
                            memory[PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[PC.get() + 1u] = static_cast<std::uint8_t>(addr);
                            memory[PC.get() + 2u] = static_cast<std::uint8_t>(addr >> 8);
                        }
                    }
                }
                break;
            }
            case Addressing::Relative:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::Relative)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();

                        if(avl == AVL_type::value)
                        {
                            try
                            {
                                const auto offset = std::stoi(val);
                                if(offset >= -126 && offset <= 129)
                                {
                                    memory[reg.PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                                    memory[reg.PC.get() + 1] = static_cast<cpu6502::Byte>(offset - 2);
                                    matched = Addressing::Relative;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if(avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                const auto label_val = static_cast<std::int32_t>(find_label->second);
                                const auto PC_val = static_cast<std::int32_t>(reg.PC.get() + 2);
                                const auto diff = label_val - PC_val;
                                if(diff >= -128 && diff <= 127)
                                {
                                    matched = Addressing::Relative;
                                    memory[reg.PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                                    memory[reg.PC.get() + 1] = static_cast<cpu6502::Byte>(diff);
                                }
                            }
                        }

                    }
                }
                break;
            }
            case Addressing::Indirect:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::Indirect)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();
                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = ai.get_val_as_uint32();
                                if(iaddr < std::numeric_limits<std::uint16_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::Indirect;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if(avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                const auto label_val = static_cast<std::uint32_t>(find_label->second);
                                if(label_val < std::numeric_limits<std::uint16_t>::max())
                                {
                                    addr = label_val;
                                    matched = Addressing::Indirect;
                                }
                            }
                        }

                        if(matched == Addressing::Indirect)
                        {
                            memory[reg.PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[reg.PC.get() + 1] = static_cast<cpu6502::Byte>(addr);
                            memory[reg.PC.get() + 2] = static_cast<cpu6502::Byte>(addr >> 8);
                        }
                    }
                }
                break;
            }
            case Addressing::IndirectX:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::IndirectX)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();
                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = static_cast<std::uint32_t>(std::stoul(val, 0, 16));
                                const auto add_irx_offset = iaddr + static_cast<std::uint32_t>(reg.IRX.get());
                                if(add_irx_offset <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::IndirectX;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if(avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                const auto label_val = static_cast<std::uint32_t>(find_label->second);
                                const auto add_irx_offset = label_val + static_cast<std::uint32_t>(reg.IRX.get());
                                if(add_irx_offset <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = label_val;
                                    matched = Addressing::IndirectX;
                                }
                            }
                        }

                        if(matched == Addressing::IndirectX)
                        {
                            memory[reg.PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[reg.PC.get() + 1] = static_cast<cpu6502::Byte>(addr);
                        }
                    }
                }
                break;
            }
            case Addressing::IndirectY:
            {
                for(const auto& ai : addressing_info)
                {
                    if(ai.get_mode() == Addressing::IndirectY)
                    {
                        const auto avl = ai.get_avl();
                        const auto& val = ai.get_value();
                        std::uint32_t addr = std::numeric_limits<std::uint32_t>::max();
                        if(avl == AVL_type::address)
                        {
                            try
                            {
                                const auto iaddr = static_cast<std::uint32_t>(std::stoul(val, 0, 16));
                                const auto add_iry_offset = iaddr + static_cast<std::uint32_t>(reg.IRY.get());
                                if(add_iry_offset <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = iaddr;
                                    matched = Addressing::IndirectY;
                                }
                            }
                            catch(const std::exception&)
                            {
                            }
                        }
                        else if(avl == AVL_type::label)
                        {
                            auto find_label = m_labels.find(to_upper(val));
                            if(find_label != m_labels.end())
                            {
                                const auto label_val = static_cast<std::uint32_t>(find_label->second);
                                const auto add_iry_offset = label_val + static_cast<std::uint32_t>(reg.IRY.get());
                                if(add_iry_offset <= std::numeric_limits<std::uint8_t>::max())
                                {
                                    addr = label_val;
                                    matched = Addressing::IndirectY;
                                }
                            }
                        }

                        if(matched == Addressing::IndirectY)
                        {
                            memory[reg.PC.get()] = static_cast<cpu6502::Byte>(op_code_val);
                            memory[reg.PC.get() + 1] = static_cast<cpu6502::Byte>(addr);
                        }
                    }
                }
                break;
            }
            default:
            {
                return Addressing::BAD_ADDRESING_MODE;
                break;
            }
        }

        if(matched != Addressing::BAD_ADDRESING_MODE)
        {
            break;
        }
    }

    if(matched == Addressing::BAD_ADDRESING_MODE)
    {
        throw exceptions::bad_addressing_mode{};
    }

    return matched;
}

}  //namespace

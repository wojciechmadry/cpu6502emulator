#include "utility/utility.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::utils
{
    void load_value_to_reg(cpu6502::CPU& cpu, cpu6502::Byte value, cpu6502::Byte opcode)
    {
        auto& memory = cpu.get_memory();
        const auto set_ACU_opcode = opcode; // 2 cycles
        auto PC = cpu.get_registers().PC.get();
        memory[PC++] = set_ACU_opcode;
        const auto value_casted = static_cast<cpu6502::Byte>(value);
        memory[PC++] = value_casted;
        cpu.execute(2);
    }

    void jump_to_2020(cpu6502::CPU& cpu) 
    {
        auto& memory = cpu.get_memory();
        auto PC = cpu.get_registers().PC.get();
        memory[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute);
        memory[PC++] = 0x20;
        memory[PC++] = 0x20;
        cpu.execute(3);
    }

    void load_to_acu(cpu6502::CPU& cpu, cpu6502::Byte value)
    {
        load_value_to_reg(cpu, value, static_cast<cpu6502::Byte>(cpu6502::opcode::LDA::Immediate));
    }

    void load_to_xreg(cpu6502::CPU& cpu, cpu6502::Byte value)
    {
        load_value_to_reg(cpu, value, static_cast<cpu6502::Byte>(cpu6502::opcode::LDX::Immediate));
    }

    void load_to_yreg(cpu6502::CPU& cpu, cpu6502::Byte value)
    {
        load_value_to_reg(cpu, value, static_cast<cpu6502::Byte>(cpu6502::opcode::LDY::Immediate));
    }

    void push_to_stack(cpu6502::CPU& cpu, cpu6502::Byte value)
    {
        auto& memory = cpu.get_memory();
        load_to_acu(cpu, value);
        auto PC = cpu.get_registers().PC.get();
        memory[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::PHA::Implied); // 3 cycles
        cpu.execute(3);

    }

    cpu6502::Byte pop_from_stack(cpu6502::CPU& cpu)
    {

        auto PC = cpu.get_registers().PC.get();
        auto& memroy = cpu.get_memory();

        memroy[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::PLA::Implied); // 4 cycles
        cpu.execute(4);

        const auto ACU = cpu.get_registers().ACU.get();

        return ACU;
    }

}
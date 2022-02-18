#include "instruction_test.hpp"

#include "cpu.hpp"

#include <limits>

namespace CPU6502_TEST::inner{
    bool DEY_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;


        auto PC = cpu.get_registers().PC.get();

        auto JUMP_TO_2020 = [&]()
        {
            PC = cpu.get_registers().PC.get();
            mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute);
            mem[PC++] = 0x20;
            mem[PC++] = 0x20;
            cpu.execute(3);
            cpu.get_registers().PS.put_byte(0x00);
            PC = cpu.get_registers().PC.get();
            all_good &= PC == 0x2020;
        };

        auto load_to_acu = [&]<typename INT, typename OPCODE = cpu6502::opcode::LDA>(INT value, OPCODE op = cpu6502::opcode::LDA::Immediate)
        {
            const auto set_ACU_opcode = static_cast<decltype(opcode)>(op); // 2 cycles
            PC = cpu.get_registers().PC.get();
            mem[PC++] = set_ACU_opcode;
            const auto value_casted = static_cast<cpu6502::Byte>(value);
            mem[PC++] = value_casted;
            cpu.execute(2);
        };

        auto load_to_xreg = [&]<typename INT>(INT value)
        {
            load_to_acu(value, cpu6502::opcode::LDX::Immediate);
        };

        auto load_to_yreg = [&]<typename INT>(INT value)
        {
            load_to_acu(value, cpu6502::opcode::LDY::Immediate);
        };
        load_to_yreg(5);
        load_to_xreg(5);

        JUMP_TO_2020();

        // ASSERT DEY - Implied
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::DEY::Implied); // 2 cycles
            for(cpu6502::Word i = 0u; i < 255u ; ++i)
            {
                load_to_yreg(i);
                mem[PC++] = opcode;
                cpu.execute(2);

                const auto result = static_cast<cpu6502::Byte>(i - 1);
                const auto zero_flag = result == 0;
                const auto negative_flag = static_cast<bool>(result & 0x80);

                all_good &= result == cpu.get_registers().IRY.get();

                all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

                all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
            }
        }
        // END ASSERT DEY - Implied

        return all_good;
    }
}
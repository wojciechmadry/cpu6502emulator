#include "instruction_test.hpp"

#include "cpu.hpp"

#include <limits>
#include <iostream>
namespace CPU6502_TEST::inner{
    bool ADC_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;
        const auto set_ACU_opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::Immediate); // 2 cycles


        auto PC = cpu.get_registers().PC.get();

        auto JUMP_TO_2020 = [&]()
        {
            PC = cpu.get_registers().PC.get();
            mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute);
            mem[PC++] = 0x20;
            mem[PC++] = 0x20;
            cpu.execute(3);
            PC = cpu.get_registers().PC.get();
        };

        JUMP_TO_2020();

        //ASSERT ADC - Immediate

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Immediate); // 2 cycles

        // Signed test
        for(std::int16_t i = -128 ; i < 127 ; ++i)
        {
            for(std::int16_t j = -128 ; j < 127 ; ++j)
            {
                const auto add_res = i + j;
                // Load i to ACU
                mem[PC++] = set_ACU_opcode;
                mem[PC++] = static_cast<cpu6502::Byte>(i);
                cpu.execute(2);
                // Check ACU value before add
                all_good &= cpu.get_registers().ACU.get() == static_cast<cpu6502::Byte>(i);

                // Add ACU + j
                mem[PC++] = opcode;
                mem[PC++] = static_cast<cpu6502::Byte>(j);
                cpu.execute(2);
                // Check ACU value after add
                all_good &= cpu.get_registers().ACU.get() == static_cast<cpu6502::Byte>(add_res);

                // Check overflow flag
                all_good &= cpu.get_registers().PS.get(PSFlags::OverflowFlag) == (add_res > std::numeric_limits<cpu6502::SByte>::max() || add_res < std::numeric_limits<cpu6502::SByte>::min());

                // Check Zero flag
                all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == static_cast<bool>(static_cast<cpu6502::Byte>(add_res) == 0);

                // Check Negative flag
                all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == static_cast<bool>(add_res & 0x80);

                // Clear carry and overflow flag.
                mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::CLV::Implied);
                mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::CLC::Implied);
                cpu.execute(4);

                JUMP_TO_2020();
            }
        }

        // Unsigned test
        for(std::uint16_t i = 0 ; i <= 255 ; ++i)
        {
            for(std::uint16_t j = 0 ; j <= 255 ; ++j)
            {
                const auto add_res = i + j;
                // Load i to ACU
                mem[PC++] = set_ACU_opcode;
                mem[PC++] = static_cast<cpu6502::Byte>(i);
                cpu.execute(2);
                // Check ACU value before add
                all_good &= cpu.get_registers().ACU.get() == static_cast<cpu6502::Byte>(i);

                // Add ACU + j
                mem[PC++] = opcode;
                mem[PC++] = static_cast<cpu6502::Byte>(j);
                cpu.execute(2);
                // Check ACU value after add
                all_good &= cpu.get_registers().ACU.get() == static_cast<cpu6502::Byte>(add_res);

                // Check carry flag
                all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == (add_res > std::numeric_limits<cpu6502::Byte>::max());

                // Check Zero flag
                all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == static_cast<bool>(static_cast<cpu6502::Byte>(add_res) == 0);

                // Check Negative flag
                all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == static_cast<bool>(add_res & 0x80);

                // Clear carry and overflow flag.
                mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::CLV::Implied);
                mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::CLC::Implied);
                cpu.execute(4);

                JUMP_TO_2020();
            }
        }
        JUMP_TO_2020();

/*

        mem[PC++] = opcode;
        mem[PC++] = 40;
        cpu.execute(2);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0;
        cpu.execute(2);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 128;
        cpu.execute(2);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));*/
        //END ASSERT ADC - Immediate

        return all_good;
    }
}
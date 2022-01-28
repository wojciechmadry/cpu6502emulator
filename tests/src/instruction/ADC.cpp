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

        //ASSERT ADC - Immediate

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Immediate); // 2 cycles

        // Signed test
        for(std::int16_t i = -128 ; i < 127 ; ++i)
        {
            for(std::int16_t j = -128 ; j < 127 ; ++j)
            {
                const auto add_res = i + j;
                // Load i to ACU
                load_to_acu(i);

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
                load_to_acu(i);

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

        //END ASSERT ADC - Immediate

        //ASSERT ADC - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::ZeroPage); // 3 Cycles

        load_to_acu(37);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);

        all_good &= cpu.get_registers().ACU.get() == 40 + 37;


        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0x5;
        cpu.execute(3);

        all_good &=cpu.get_registers().ACU.get() == 40 + 37 + 0x5;

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(3);

        all_good &= cpu.get_registers().ACU.get() == static_cast<cpu6502::Byte>(40 + 37 + 0x5 + 128);
        //END ASSERT ADC - Zero Page

        JUMP_TO_2020();

        //ASSERT ADC - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::ZeroPageX); // 4 Cycles
        load_to_xreg(15);
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x0F;
        mem[0x0F + 15] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 40 + 30;


        mem[PC++] = opcode;
        mem[PC++] = 0xAA;
        mem[0xAA + 15] = 0x5;
        cpu.execute(4);

        all_good &=cpu.get_registers().ACU.get() == 40 + 30 + 0x5;

        mem[PC++] = opcode;
        mem[PC++] = 0xBA;
        mem[0xBA + 15] = 120;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == static_cast<cpu6502::Byte>(40 + 30 + 0x5 + 120);
        //END ASSERT ADC - Zero Page X
        JUMP_TO_2020();
        
        //ASSERT ADC - Absolute
        //END ASSERT ADC - Absolute

        //ASSERT ADC - Absolute X
        //END ASSERT ADC - Absolute X

        //ASSERT ADC - Absolute Y
        //END ASSERT ADC - Absolute Y

        //ASSERT ADC - Indirect X
        //END ASSERT ADC - Indirect X

        //ASSERT ADC - Indirect Y
        //END ASSERT ADC - Indirect Y
        return all_good;
    }
}
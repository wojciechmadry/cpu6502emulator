#include "instruction_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"

#include <limits>

namespace CPU6502_TEST::inner{
    bool ADC_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;


        cpu6502::registers::ProgramCounter::RegisterStroedType PC;

        utils::jump_to_2020(cpu);

        //ASSERT ADC - Immediate

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Immediate); // 2 cycles

        // Signed test
        for(std::int16_t i = -128 ; i < 127 ; ++i)
        {
            for(std::int16_t j = -128 ; j < 127 ; ++j)
            {
                const auto add_res = i + j;
                // Load i to ACU
                utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(i));
                PC = cpu.get_registers().PC.get();

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

                utils::jump_to_2020(cpu);
            }
        }

        // Unsigned test
        for(std::uint16_t i = 0 ; i <= 255 ; ++i)
        {
            for(std::uint16_t j = 0 ; j <= 255 ; ++j)
            {
                const auto add_res = i + j;
                // Load i to ACU
                utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(i));
                PC = cpu.get_registers().PC.get();

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

                utils::jump_to_2020(cpu);
            }
        }
        utils::jump_to_2020(cpu);

        //END ASSERT ADC - Immediate

        //ASSERT ADC - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::ZeroPage); // 3 Cycles

        utils::load_to_acu(cpu, 37);
        PC = cpu.get_registers().PC.get();


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

        utils::jump_to_2020(cpu);

        //ASSERT ADC - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::ZeroPageX); // 4 Cycles
        utils::load_to_xreg(cpu, 15);
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();


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

        utils::jump_to_2020(cpu);
        
        //ASSERT ADC - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Absolute);
        
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 70;

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0x15;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 70 + 0x15;

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 1;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 70 + 0x15 + 1;
        //END ASSERT ADC - Absolute

        utils::jump_to_2020(cpu);

        //ASSERT ADC - Absolute X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::AbsoluteX);
        utils::load_to_xreg(cpu, 10);
        utils::load_to_acu(cpu, 15);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 40 + 15;
        
        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[PC++] = 0x00;
        mem[0x00FF + 10] = 5;
        cpu.execute(5);

        all_good &= cpu.get_registers().ACU.get() == 40 + 15 + 5;

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 128;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 40 + 15 + 5 + 128;
        //END ASSERT ADC - Absolute X
        
        utils::jump_to_2020(cpu);

        //ASSERT ADC - Absolute Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::AbsoluteY);
        utils::load_to_yreg(cpu, 10);
        utils::load_to_acu(cpu, 15);
        PC = cpu.get_registers().PC.get();


        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 40 + 15;
        
        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[PC++] = 0x00;
        mem[0x00FF + 10] = 5;
        cpu.execute(5);

        all_good &= cpu.get_registers().ACU.get() == 40 + 15 + 5;

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 128;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() == 40 + 15 + 5 + 128;
        //END ASSERT ADC - Absolute Y

        utils::jump_to_2020(cpu);

        //ASSERT ADC - Indirect X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::IndirectX);
        utils::load_to_xreg(cpu, 10);
        utils::load_to_acu(cpu, 15);
        PC = cpu.get_registers().PC.get();


        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(6);
        all_good &= cpu.get_registers().ACU.get() == 15 + 40;

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 2;
        cpu.execute(6);
        all_good &= cpu.get_registers().ACU.get() == 15 + 40 + 2;

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(6);

        all_good &= cpu.get_registers().ACU.get() == 15 + 40 + 2 + 128;
        //END ASSERT ADC - Indirect X

        utils::jump_to_2020(cpu);
        
        //ASSERT ADC - Indirect Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::IndirectY);
        utils::load_to_yreg(cpu, 10);
        utils::load_to_acu(cpu, 15);
        PC = cpu.get_registers().PC.get();


        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(5);
        all_good &= cpu.get_registers().ACU.get() == 15 + 40;

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0xFF;
        mem[0x21] = 0x00;
        mem[0x00FF + 10] = 2;
        cpu.execute(6);
        all_good &= cpu.get_registers().ACU.get() == 15 + 40 + 2;

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741 + 10] = 128;
        cpu.execute(5);

        all_good &= cpu.get_registers().ACU.get() == 15 + 40 + 2 + 128;
        //END ASSERT ADC - Indirect Y
        return all_good;
    }
}
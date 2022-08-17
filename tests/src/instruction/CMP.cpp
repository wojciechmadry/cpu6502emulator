#include "instruction_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool CMP_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        utils::jump_to_2020(cpu);
        cpu6502::registers::ProgramCounter::RegisterStroedType PC;

        //ASSERT CMP - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::Immediate); // 2 cycles

        for(std::int16_t i = -100 ; i <= 100 ; ++i)
        {
            for(std::int16_t j = -100; j <= 100 ; ++j)
            {
                // i -> acu
                // j -> memory
                const auto carry_flag = static_cast<cpu6502::Byte>(i) >= static_cast<cpu6502::Byte>(j);
                const auto zero_flag = i == j;
                const auto result = static_cast<cpu6502::Byte>(i - j);
                const auto negative_flag = static_cast<bool>(result & 0x80);
                // Load i to ACU
                utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(i));
                PC = cpu.get_registers().PC.get();

                // Compare ACU with J (memory)
                mem[PC++] = opcode;
                mem[PC++] = static_cast<cpu6502::Byte>(j);
                cpu.execute(2);

                // Check Negative flag
                all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == negative_flag;

                // Check Carry Flag
                all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == carry_flag;

                // Check Zero Flag
                all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == zero_flag;

                utils::jump_to_2020(cpu);
            }
        }
        //END ASSERT CMP - Immediate
        
        utils::jump_to_2020(cpu);

        //ASSERT CMP - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::ZeroPage); // 3 Cycles

        utils::load_to_acu(cpu, 37);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0x5;
        cpu.execute(3);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0;
        cpu.execute(3);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        //END ASSERT CMP - Zero Page

        utils::jump_to_2020(cpu);

        //ASSERT CMP - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::ZeroPageX); // 4 Cycles
        utils::load_to_xreg(cpu, 15);
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x0F;
        mem[0x0F + 15] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xAA;
        mem[0xAA + 15] = 0x5;
        cpu.execute(4);


        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xBA;
        mem[0xBA + 15] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        //END ASSERT CMP - Zero Page X

        utils::jump_to_2020(cpu);

        //ASSERT CMP - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::Absolute);

        for(std::int16_t i = -15 ; i <= 15 ; ++i)
        {
            for(std::int16_t j = -15; j <= 15 ; ++j)
            {
                // i -> acu
                // j -> memory
                const auto carry_flag = static_cast<cpu6502::Byte>(i) >= static_cast<cpu6502::Byte>(j);
                const auto zero_flag = i == j;
                const auto result = static_cast<cpu6502::Byte>(i - j);
                const auto negative_flag = static_cast<bool>(result & 0x80);
                // Load i to ACU
                utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(i));
                PC = cpu.get_registers().PC.get();

                // Compare ACU with J (memory)
                 mem[PC++] = opcode;
                mem[PC++] = 0x41;
                mem[PC++] = 0x47;
                mem[0x4741] = static_cast<cpu6502::Byte>(j);
                cpu.execute(4);

                // Check Negative flag
                all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == negative_flag;

                // Check Carry Flag
                all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == carry_flag;

                // Check Zero Flag
                all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == zero_flag;

                utils::jump_to_2020(cpu);
            }
        }
        
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0x5;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        //END ASSERT CMP - Absolute

        utils::jump_to_2020(cpu);


        //ASSERT CMP - Absolute X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::AbsoluteX);
        utils::load_to_xreg(cpu, 10);
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[PC++] = 0x00;
        mem[0x00FF + 10] = 0x5;
        cpu.execute(5);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        //END ASSERT CMP - Absolute X
        
        utils::jump_to_2020(cpu);

        //ASSERT CMP - Absolute Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::AbsoluteY);
        utils::load_to_yreg(cpu, 10);
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[PC++] = 0x00;
        mem[0x00FF + 10] = 0x5;
        cpu.execute(5);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        //END ASSERT CMP - Absolute Y

        utils::jump_to_2020(cpu);

        //ASSERT CMP - Indirect X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::IndirectX);
        utils::load_to_xreg(cpu, 10);
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(6);
        
        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 0x5;
        cpu.execute(6);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 0;
        cpu.execute(6);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        //END ASSERT CMP - Indirect X

        utils::jump_to_2020(cpu);

        //ASSERT CMP - Indirect Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::IndirectY);
        utils::load_to_yreg(cpu, 10);
        utils::load_to_acu(cpu, 30);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(5);
        
        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        utils::load_to_acu(cpu, 0x5);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0xFF;
        mem[0x21] = 0x00;
        mem[0x00FF + 10] = 0x5;
        cpu.execute(6);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        utils::load_to_acu(cpu, 0xFF);
        PC = cpu.get_registers().PC.get();

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741 + 10] = 0;
        cpu.execute(5);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        //END ASSERT CMP - Indirect Y

        return all_good;
    }
}
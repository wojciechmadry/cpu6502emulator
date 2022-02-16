#include "instruction_test.hpp"

#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool CMP_TEST()
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

        //ASSERT CMP - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::Immediate); // 2 cycles

        for(std::int16_t i = -25 ; i <= 25 ; ++i)
        {
            for(std::int16_t j = -25; j <= 25 ; ++j)
            {
                // i -> acu
                // j -> memory
                const auto carry_flag = static_cast<cpu6502::Byte>(i) >= static_cast<cpu6502::Byte>(j);
                const auto zero_flag = i == j;
                const auto result = static_cast<cpu6502::Byte>(i - j);
                const auto negative_flag = static_cast<bool>(result & 0x80);
                // Load i to ACU
                load_to_acu(i);

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

                JUMP_TO_2020();
            }
        }
        //END ASSERT CMP - Immediate
        
        JUMP_TO_2020();

        //ASSERT CMP - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::ZeroPage); // 3 Cycles

        load_to_acu(37);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0x5;
        cpu.execute(3);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0;
        cpu.execute(3);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        //END ASSERT CMP - Zero Page

        JUMP_TO_2020();

        //ASSERT CMP - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::ZeroPageX); // 4 Cycles
        load_to_xreg(15);
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x0F;
        mem[0x0F + 15] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0xAA;
        mem[0xAA + 15] = 0x5;
        cpu.execute(4);


        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

        mem[PC++] = opcode;
        mem[PC++] = 0xBA;
        mem[0xBA + 15] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        //END ASSERT CMP - Zero Page X

        JUMP_TO_2020();

        //ASSERT CMP - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::Absolute);
        
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0x5;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        //END ASSERT CMP - Absolute

        JUMP_TO_2020();


        //ASSERT CMP - Absolute X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::AbsoluteX);
        load_to_xreg(10);
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[PC++] = 0x00;
        mem[0x00FF + 10] = 0x5;
        cpu.execute(5);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        //END ASSERT CMP - Absolute X
        
        JUMP_TO_2020();

        //ASSERT CMP - Absolute Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::AbsoluteY);
        load_to_yreg(10);
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        
        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[PC++] = 0x00;
        mem[0x00FF + 10] = 0x5;
        cpu.execute(5);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741 + 10] = 0;
        cpu.execute(4);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;
        //END ASSERT CMP - Absolute Y

        JUMP_TO_2020();

        //ASSERT CMP - Indirect X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::IndirectX);
        load_to_xreg(10);
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(6);
        
        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20 + 10] = 0x41;
        mem[0x21 + 10] = 0x47;
        mem[0x4741] = 0x5;
        cpu.execute(6);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

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

        JUMP_TO_2020();

        //ASSERT CMP - Indirect Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::CMP::IndirectY);
        load_to_yreg(10);
        load_to_acu(30);

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741 + 10] = 40;
        cpu.execute(5);
        
        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == false;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == true;

        load_to_acu(0x5);

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0xFF;
        mem[0x21] = 0x00;
        mem[0x00FF + 10] = 0x5;
        cpu.execute(6);

        all_good &= cpu.get_registers().PS.get(PSFlags::ZeroFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag) == true;
        all_good &= cpu.get_registers().PS.get(PSFlags::NegativeFlag) == false;

        load_to_acu(0xFF);

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
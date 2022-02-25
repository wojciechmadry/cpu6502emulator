#include "instruction_test.hpp"

#include "utility/utility.hpp"
#include "cpu.hpp"

#include <limits>

namespace CPU6502_TEST::inner{
    bool LSR_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        utils::jump_to_2020(cpu);
        auto PC = cpu.get_registers().PC.get();

        // ASSERT LSR - Accumulator
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LSR::Accumulator); // 2 cycles
    
        for(cpu6502::Word i = 0u ; i <= 255u ; ++i)
        {
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(i));
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            cpu.execute(2);

            const auto result = static_cast<cpu6502::Byte>(i >> 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(i & 0x01);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == cpu.get_registers().ACU.get();

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);


        }

        // END ASSERT LSR - Accumulator

        utils::jump_to_2020(cpu);
        PC = cpu.get_registers().PC.get();

        // ASSERT LSR - Zero Page
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LSR::ZeroPage); // 5 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            mem[PC++] = opcode;
            mem[PC++] = 0x20;
            const auto zero_page_val = static_cast<cpu6502::Byte>(15);
            mem[0x20] = zero_page_val;
            cpu.execute(5);

            const auto result = static_cast<cpu6502::Byte>(zero_page_val >> 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(zero_page_val & 0x01);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x20];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT LSR - Zero Page

        utils::jump_to_2020(cpu);
        PC = cpu.get_registers().PC.get();

        // ASSERT LSR - Zero Page X
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LSR::ZeroPageX); // 6 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            utils::load_to_xreg(cpu, 0x10);
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            mem[PC++] = 0x20;
            const auto zero_page_val = static_cast<cpu6502::Byte>(15);
            mem[0x20 + 0x10] = zero_page_val;
            cpu.execute(6);

            const auto result = static_cast<cpu6502::Byte>(zero_page_val >> 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(zero_page_val & 0x01);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x20 + 0x10];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT LSR - Zero Page X

        utils::jump_to_2020(cpu);
        PC = cpu.get_registers().PC.get();  

        // ASSERT LSR - Absolute
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LSR::Absolute); // 6 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            mem[PC++] = opcode;
            mem[PC++] = 0x44;
            mem[PC++] = 0x44;
            const auto absolute_val = static_cast<cpu6502::Byte>(10);
            mem[0x4444] = absolute_val;
            cpu.execute(6);

            const auto result = static_cast<cpu6502::Byte>(absolute_val >> 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(absolute_val & 0x01);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x4444];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT LSR - Absolute

        utils::jump_to_2020(cpu);

        // ASSERT LSR - Absolute X
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LSR::AbsoluteX); // 7 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            utils::load_to_xreg(cpu, 0x10);
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            mem[PC++] = 0x44;
            mem[PC++] = 0x44;
            const auto absolute_val = static_cast<cpu6502::Byte>(10);
            mem[0x4444 + 0x10] = absolute_val;
            cpu.execute(7);

            const auto result = static_cast<cpu6502::Byte>(absolute_val >> 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(absolute_val & 0x01);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x4444 + 0x10];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT LSR - Absolute X

        return all_good;
    }
}
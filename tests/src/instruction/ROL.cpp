#include "instruction_test.hpp"

#include "utility/utility.hpp"
#include "cpu.hpp"

#include <limits>

namespace CPU6502_TEST::inner{
    bool ROL_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;


        utils::jump_to_2020(cpu);
        auto PC = cpu.get_registers().PC.get();


        // ASSERT ROL - Accumulator
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ROL::Accumulator); // 2 cycles
    
        for(cpu6502::Word i = 0u ; i <= 255u ; ++i)
        {
            bool should_be_carry = i%2 == 0;
            if (should_be_carry)
            {
                cpu.get_registers().PS.set(PSFlags::CarryFlag, true);
            }
            else
            {
                cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            }

            utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(i));
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            cpu.execute(2);

            const auto result = static_cast<cpu6502::Byte>((i << 1) | static_cast<int>(should_be_carry));
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(i & 0x80);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == cpu.get_registers().ACU.get();

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);


        }

        // END ASSERT ROL - Accumulator

        utils::jump_to_2020(cpu);
        PC = cpu.get_registers().PC.get();

        // ASSERT ROL - Zero Page
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ROL::ZeroPage); // 5 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            mem[PC++] = opcode;
            mem[PC++] = 0x20;
            const auto zero_page_val = static_cast<cpu6502::Byte>(15);
            mem[0x20] = zero_page_val;
            cpu.execute(5);

            const auto result = static_cast<cpu6502::Byte>(zero_page_val << 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(zero_page_val & 0x80);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x20];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT ROL - Zero Page

        utils::jump_to_2020(cpu);

        // ASSERT ROL - Zero Page X
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ROL::ZeroPageX); // 6 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            utils::load_to_xreg(cpu, 0x10);
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            mem[PC++] = 0x20;
            const auto zero_page_val = static_cast<cpu6502::Byte>(15);
            mem[0x20 + 0x10] = zero_page_val;
            cpu.execute(6);

            const auto result = static_cast<cpu6502::Byte>(zero_page_val << 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(zero_page_val & 0x80);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x20 + 0x10];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT ROL - Zero Page X

        utils::jump_to_2020(cpu);
        PC = cpu.get_registers().PC.get();

        // ASSERT ROL - Absolute
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ROL::Absolute); // 6 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            mem[PC++] = opcode;
            mem[PC++] = 0x44;
            mem[PC++] = 0x44;
            const auto absolute_val = static_cast<cpu6502::Byte>(10);
            mem[0x4444] = absolute_val;
            cpu.execute(6);

            const auto result = static_cast<cpu6502::Byte>(absolute_val << 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(absolute_val & 0x80);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x4444];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT ROL - Absolute

        utils::jump_to_2020(cpu);

        // ASSERT ROL - Absolute X
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ROL::AbsoluteX); // 7 cycles
            cpu.get_registers().PS.set(PSFlags::CarryFlag, false);
            utils::load_to_xreg(cpu, 0x10);
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            mem[PC++] = 0x44;
            mem[PC++] = 0x44;
            const auto absolute_val = static_cast<cpu6502::Byte>(10);
            mem[0x4444 + 0x10] = absolute_val;
            cpu.execute(7);

            const auto result = static_cast<cpu6502::Byte>(absolute_val << 1);
            const auto zero_flag = result == 0;
            const auto carry_flag = static_cast<bool>(absolute_val & 0x80);
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x4444 + 0x10];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= carry_flag == cpu.get_registers().PS.get(PSFlags::CarryFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT ROL - Absolute X

        return all_good;
    }
}
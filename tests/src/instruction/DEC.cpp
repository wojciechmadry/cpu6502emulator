#include "instruction_test.hpp"

#include <limits>
#include "cpu.hpp"
#include "utility/test_utils.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool DEC_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;


        utils::jump_to_2020(cpu) ;
        auto PC = cpu.get_registers().PC.get();

        // ASSERT DEC - Zero Page
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::DEC::ZeroPage); // 5 cycles
            for(cpu6502::Word i = 0u; i < 255u ; ++i)
            {
                mem[PC++] = opcode;
                mem[PC++] = 0x20;
                const auto zero_page_val = static_cast<cpu6502::Byte>(i);
                mem[0x20] = zero_page_val;
                cpu.execute(5);

                const auto result = static_cast<cpu6502::Byte>(zero_page_val - 1);
                const auto zero_flag = result == 0;
                const auto negative_flag = static_cast<bool>(result & 0x80);

                all_good &= result == mem[0x20];

                all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

                all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
            }
        }
        // END ASSERT DEC - Zero Page

        utils::jump_to_2020(cpu) ;

        // ASSERT DEC - Zero Page X
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::DEC::ZeroPageX); // 6 cycles
            utils::load_to_xreg(cpu, 0x10);
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            mem[PC++] = 0x20;
            const auto zero_page_val = static_cast<cpu6502::Byte>(15);
            mem[0x20 + 0x10] = zero_page_val;
            cpu.execute(6);

            const auto result = static_cast<cpu6502::Byte>(zero_page_val - 1);
            const auto zero_flag = result == 0;
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x20 + 0x10];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT DEC - Zero Page X

        utils::jump_to_2020(cpu) ;
        PC = cpu.get_registers().PC.get();
        
        // ASSERT DEC - Absolute
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::DEC::Absolute); // 6 cycles
            mem[PC++] = opcode;
            mem[PC++] = 0x44;
            mem[PC++] = 0x44;
            const auto absolute_val = static_cast<cpu6502::Byte>(10);
            mem[0x4444] = absolute_val;
            cpu.execute(6);

            const auto result = static_cast<cpu6502::Byte>(absolute_val - 1);
            const auto zero_flag = result == 0;
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x4444];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT DEC - Absolute

        utils::jump_to_2020(cpu) ;

        // ASSERT DEC - Absolute X
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::DEC::AbsoluteX); // 7 cycles
            utils::load_to_xreg(cpu, 0x10);
            PC = cpu.get_registers().PC.get();
            mem[PC++] = opcode;
            mem[PC++] = 0x44;
            mem[PC++] = 0x44;
            const auto absolute_val = static_cast<cpu6502::Byte>(10);
            mem[0x4444 + 0x10] = absolute_val;
            cpu.execute(7);

            const auto result = static_cast<cpu6502::Byte>(absolute_val - 1);
            const auto zero_flag = result == 0;
            const auto negative_flag = static_cast<bool>(result & 0x80);

            all_good &= result == mem[0x4444 + 0x10];

            all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

            all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
        }
        // END ASSERT DEC - Absolute X

        return all_good;
    }
}
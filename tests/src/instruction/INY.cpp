#include "instruction_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"

#include <limits>

namespace CPU6502_TEST::inner{
    bool INY_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        utils::jump_to_2020(cpu);
        cpu6502::registers::ProgramCounter::RegisterStroedType PC;

        // ASSERT INY - Implied
        {
            opcode = static_cast<decltype(opcode)>(cpu6502::opcode::INY::Implied); // 2 cycles
            for(cpu6502::Word i = 0u; i < 255u ; ++i)
            {
                utils::load_to_yreg(cpu, static_cast<cpu6502::Byte>(i));
                PC = cpu.get_registers().PC.get();
                mem[PC++] = opcode;
                cpu.execute(2);

                const auto result = static_cast<cpu6502::Byte>(i + 1);
                const auto zero_flag = result == 0;
                const auto negative_flag = static_cast<bool>(result & 0x80);

                all_good &= result == cpu.get_registers().IRY.get();

                all_good &= zero_flag == cpu.get_registers().PS.get(PSFlags::ZeroFlag);

                all_good &= negative_flag == cpu.get_registers().PS.get(PSFlags::NegativeFlag);
            }
        }
        // END ASSERT INY - Implied

        return all_good;
    }
}
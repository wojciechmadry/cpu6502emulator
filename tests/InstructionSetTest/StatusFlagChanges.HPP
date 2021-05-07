#ifndef cpu6502_TEST_STATUS_FLAG_CHANGES
#define cpu6502_TEST_STATUS_FLAG_CHANGES

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool STATUS_FLAG_CHANGES_TEST() noexcept
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        auto p = PSFlags::BreakCommand;
        (void) p;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;
        auto PC = cpu.get_registers().PC.get();
        mem[PC] = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
        mem[PC + 1] = 0x20;
        mem[PC + 2] = 0x20;
        cpu.execute(3);
        cpu6502::u32 last = 0x2020;
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEC::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::SED::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEI::Implied);
        cpu.execute(6);

        all_good &= (cpu.get_registers().PS.get(PSFlags::CarryFlag)
                && cpu.get_registers().PS.get(PSFlags::DecimalMode)
                && cpu.get_registers().PS.get(PSFlags::InterruptDisable));

        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLC::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLD::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLI::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLV::Implied);
        cpu.execute(8);
        all_good &= (   !cpu.get_registers().PS.get(PSFlags::CarryFlag)
                     && !cpu.get_registers().PS.get(PSFlags::DecimalMode)
                     && !cpu.get_registers().PS.get(PSFlags::InterruptDisable)
                     && !cpu.get_registers().PS.get(PSFlags::OverflowFlag)
                     );

        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEC::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::SED::Implied);
        mem[last++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEI::Implied);
        cpu.execute(6);

        all_good &= (cpu.get_registers().PS.get(PSFlags::CarryFlag)
                     && cpu.get_registers().PS.get(PSFlags::DecimalMode)
                     && cpu.get_registers().PS.get(PSFlags::InterruptDisable));

        return all_good;
    }
}

#endif
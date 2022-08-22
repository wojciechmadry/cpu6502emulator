#include "instruction_test.hpp"

#include "utility/test_utils.hpp"
#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool STATUS_FLAG_CHANGES_TEST()
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        utils::jump_to_2020(cpu);
        auto PC = cpu.get_registers().PC.get();
        
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEC::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::SED::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEI::Implied);
        cpu.execute(6);

        all_good &= (cpu.get_registers().PS.get(PSFlags::CarryFlag)
                && cpu.get_registers().PS.get(PSFlags::DecimalMode)
                && cpu.get_registers().PS.get(PSFlags::InterruptDisable));

        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLC::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLD::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLI::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::CLV::Implied);
        cpu.execute(8);
        all_good &= (   !cpu.get_registers().PS.get(PSFlags::CarryFlag)
                     && !cpu.get_registers().PS.get(PSFlags::DecimalMode)
                     && !cpu.get_registers().PS.get(PSFlags::InterruptDisable)
                     && !cpu.get_registers().PS.get(PSFlags::OverflowFlag)
                     );

        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEC::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::SED::Implied);
        mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::SEI::Implied);
        cpu.execute(6);

        all_good &= (cpu.get_registers().PS.get(PSFlags::CarryFlag)
                     && cpu.get_registers().PS.get(PSFlags::DecimalMode)
                     && cpu.get_registers().PS.get(PSFlags::InterruptDisable));

        return all_good;
    }
}

#include "instruction_test.hpp"

#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool BRK_TEST()
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        auto p = PSFlags::BreakCommand;
        (void) p;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        auto PC = cpu.get_registers().PC.get();
        mem[PC] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute); // 3 cycles
        mem[PC + 1] = 0x20;
        mem[PC + 2] = 0x20;

        cpu.execute(3);

        PC = cpu.get_registers().PC.get();

        //ASSERT LDY - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::Immediate);

        return false;
    }
}
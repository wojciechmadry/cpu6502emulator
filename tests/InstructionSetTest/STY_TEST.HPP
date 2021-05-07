#ifndef cpu6502_TEST_STY
#define cpu6502_TEST_STY

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool STY_TEST() noexcept
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        auto p = PSFlags::BreakCommand;
        (void) p;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        // STY - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::Immediate); // 2 cycles
        cpu.reset();
        auto PC = cpu.get_registers().PC.get();
        mem[PC] = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
        mem[PC + 1] = 0x42;
        mem[PC + 2] = 0x42;
        mem[0x4242] = opcode;
        mem[0x4242 + 1] = 40; // X = 40
        mem[0x4242 + 2] = static_cast<decltype(opcode)>(cpu6502::opcode::STY::ZeroPage); // 3 cycles
        mem[0x4242 + 3] = 0x42;
        cpu.execute(8);
        all_good &= (mem[0x42] == 40);
        // END STY - Zero Page

        // STY - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::Immediate); // 2 cycles
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
        mem[PC + 1] = 0x42;
        mem[PC + 2] = 0x42;
        mem[0x4242] = opcode;
        mem[0x4242 + 1] = 40; // ACU = 40
        mem[0x4242 + 2] = static_cast<decltype(opcode)>(cpu6502::opcode::LDX::Immediate);  // 2 cycles
        mem[0x4242 + 3] = 0x18; // X register = 0x18
        mem[0x4242 + 4] = static_cast<decltype(opcode)>(cpu6502::opcode::STY::ZeroPageX); // 4 cycles
        mem[0x4242 + 5] = 0x42;
        cpu.execute(11);
        all_good &= (mem[0x42 + 0x18] == 40);
        // END STY - Zero Page X

        // STY - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::Immediate); // 2 cycles
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Absolute); // 3 cycles Jump to 0x4242
        mem[PC + 1] = 0x42;
        mem[PC + 2] = 0x42;
        mem[0x4242] = opcode;
        mem[0x4242 + 1] = 40; // ACU = 40
        mem[0x4242 + 2] = static_cast<decltype(opcode)>(cpu6502::opcode::STY::Absolute); // 4 cycles
        mem[0x4242 + 3] = 0x30;
        mem[0x4242 + 4] = 0x30;
        cpu.execute(9);
        all_good &= (mem[0x3030] == 40);
        // END STY - Absolute

        return all_good;
    }
}

#endif
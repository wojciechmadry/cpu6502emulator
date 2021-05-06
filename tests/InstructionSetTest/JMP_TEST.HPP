#ifndef cpu6502_TEST_JMP
#define cpu6502_TEST_JMP

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool JMP_TEST() noexcept
    {
        //using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Absolute);

        auto PC = cpu.get_registers().PC.get();
        //ASSERT JMP - Absolute
        mem[PC] = opcode;
        mem[PC+1] = 0x42;
        mem[PC+2] = 0x42;
        cpu.execute(3);
        assert(cpu.get_registers().PC.get() == 0x4242);
        //END ASSERT JMP - Absolute

        //ASSERT JMP - Indirect
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::JMP::Indirect);
        cpu.reset();
        mem[PC] = opcode;
        mem[PC+1] = 0x42;
        mem[PC+2] = 0x42;
        mem[0x4242] = 0x20;
        mem[0x4242+1] = 0x20;
        cpu.execute(5);
        assert(cpu.get_registers().PC.get() == 0x2020);
        //END ASSERT JMP - Indirect
        return true;
    }
}
#endif
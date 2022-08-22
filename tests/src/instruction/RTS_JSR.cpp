#include "instruction_test.hpp"

#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool RTS_JSR_TEST()
    {
        bool all_good = true;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;
        auto PC = cpu.get_registers().PC.get();

        //ASSERT RTS - Implied && JSR
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::JSR::Absolute);
        mem[PC] = opcode; // 6cycles
        mem[PC+1] = 0x42;
        mem[PC+2] = 0x42;
        mem[0x4242] = static_cast<cpu6502::Byte>(cpu6502::opcode::LDA::Immediate); //2 cycles
        mem[0x4243] = 84;
        mem[0x4244] = opcode; // 6cycles
        mem[0x4245] = 0x20;
        mem[0x4246] = 0x20;
        mem[0x2020] = static_cast<cpu6502::Byte>(cpu6502::opcode::RTS::Implied); // 6 cycles;
        mem[0x4244 + 3] = static_cast<cpu6502::Byte>(cpu6502::opcode::RTS::Implied); // 6 cycles;


        cpu.execute(26);
        all_good &= (cpu.get_registers().ACU.get() == 84);
        all_good &= (cpu.get_registers().PC.get() == PC + 3);
        //END ASSERT RTS - Implied
        return all_good;
    }
}

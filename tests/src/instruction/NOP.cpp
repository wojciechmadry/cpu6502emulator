#include "instruction_test.hpp"

#include "utility/utility.hpp"
#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool NOP_TEST()
    {
        bool all_good = true;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        utils::jump_to_2020(cpu);
        auto PC = cpu.get_registers().PC.get();

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::NOP::Implied); // 2 cycles

        mem[PC++] = opcode;

        cpu.execute(2);

        all_good &= PC == cpu.get_registers().PC.get();

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::Immediate); // 2 cycles

        mem[PC++] = opcode;
        mem[PC++] = 25;
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::NOP::Implied); // 2 cycles
        mem[PC++] = opcode;
        mem[PC + 1] = 40;

        cpu.execute(4);

        all_good &= PC == cpu.get_registers().PC.get();
        all_good &= 25 == cpu.get_registers().ACU.get();


        return all_good;
    }
}
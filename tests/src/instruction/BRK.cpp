#include "instruction_test.hpp"

#include "cpu.hpp"
#include "utility/test_utils.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool BRK_TEST()
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        utils::jump_to_2020(cpu);
        utils::load_to_acu(cpu ,10);
        
        all_good &= cpu.get_registers().ACU.get() == 10;
        auto PC = cpu.get_registers().PC.get();

        // Set IRQ address
        mem[cpu6502::CPU::IRQ] = 0x10;
        mem[cpu6502::CPU::IRQ + 1] = 0x10;


        

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::BRK::Implied); // 7 cycles
        mem[PC++] = opcode;

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Immediate); // 2 cycles
        mem[0x1010] = opcode;
        mem[0x1010 + 1] = 15;

        cpu.execute(9);

        all_good &= cpu.get_registers().ACU.get() == 15 + 10;
        all_good &= cpu.get_registers().PC.get() == 0x1010 + 2;
        all_good &= cpu.get_registers().PS.get(PSFlags::BreakCommand) == true;

        return all_good;
    }
}

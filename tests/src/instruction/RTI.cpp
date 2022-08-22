#include "instruction_test.hpp"

#include "utility/test_utils.hpp"
#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool RTI_TEST()
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;



        utils::jump_to_2020(cpu);

        utils::load_to_acu(cpu, 10);
        all_good &= cpu.get_registers().ACU.get() == 10;

        auto PC = cpu.get_registers().PC.get();
        
        // Set IRQ address
        mem[cpu6502::CPU::IRQ] = 0x10;
        mem[cpu6502::CPU::IRQ + 1] = 0x10;

        const auto register_before = cpu.get_registers();

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::BRK::Implied); // 7 cycles
        mem[PC++] = opcode;
        const auto before_brk = PC;
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Immediate); // 2 cycles
        mem[0x1010] = opcode;
        mem[0x1010 + 1] = 15;

        cpu.execute(9);

        all_good &= cpu.get_registers().ACU.get() == 15 + 10;
        all_good &= cpu.get_registers().PC.get() == 0x1010 + 2;
        all_good &= cpu.get_registers().PS.get(PSFlags::BreakCommand) == true;

        PC = cpu.get_registers().PC.get();

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::RTI::Implied); // 6 cycles

        mem[PC] = opcode;

        cpu.execute(6);

        all_good &= cpu.get_registers().PC.get() == before_brk;
        all_good &= cpu.get_registers().PS.pull_byte() == register_before.PS.pull_byte();
        all_good &= cpu.get_registers().ACU.get() == 15 + 10;

        PC = cpu.get_registers().PC.get();

        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::ADC::Immediate); // 2 cycles
        mem[PC++] = opcode;
        mem[PC++] = 5;
        cpu.execute(2);
        all_good &= cpu.get_registers().ACU.get() == 15 + 10 + 5;

        return all_good;
    }
}
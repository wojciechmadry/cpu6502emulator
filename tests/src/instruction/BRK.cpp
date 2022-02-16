#include "instruction_test.hpp"

#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool BRK_TEST()
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        auto PC = cpu.get_registers().PC.get();

        auto load_to_acu = [&]<typename INT, typename OPCODE = cpu6502::opcode::LDA>(INT value, OPCODE op = cpu6502::opcode::LDA::Immediate)
        {
            const auto set_ACU_opcode = static_cast<decltype(opcode)>(op); // 2 cycles
            PC = cpu.get_registers().PC.get();
            mem[PC++] = set_ACU_opcode;
            const auto value_casted = static_cast<cpu6502::Byte>(value);
            mem[PC++] = value_casted;
            cpu.execute(2);
        };

        load_to_acu(10);
        all_good &= cpu.get_registers().ACU.get() == 10;

        mem[PC] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute); // 3 cycles
        mem[PC + 1] = 0x20;
        mem[PC + 2] = 0x20;
        
        // Set IRQ address
        mem[cpu6502::CPU::IRQ] = 0x10;
        mem[cpu6502::CPU::IRQ + 1] = 0x10;

        cpu.execute(3);

        PC = cpu.get_registers().PC.get();

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
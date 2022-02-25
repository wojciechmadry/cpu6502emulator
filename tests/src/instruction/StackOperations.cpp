#include "instruction_test.hpp"

#include "utility/utility.hpp"
#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool STACK_OPERATIONS_TEST()
    {
        bool all_good = true;

        using PSFlags = cpu6502::CPU::PSFlags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);

        utils::jump_to_2020(cpu);
        auto PC = cpu.get_registers().PC.get();
        auto cast = []<typename T>(T OPCODE) -> cpu6502::Byte
        {
            return static_cast<cpu6502::Byte>(OPCODE);
        };

        // Transfer X to stack pointer
        mem[PC++] = cast(cpu6502::opcode::LDX::Immediate); // 2 cycles
        mem[PC++] = 0x21;
        cpu.execute(2);
        all_good &= cpu.get_registers().IRX.get() == 0x21;

        mem[PC++] = cast(cpu6502::opcode::TXS::Implied); // 2cycles
        cpu.execute(2);

        all_good = cpu.get_registers().IRX.get() == cpu.get_registers().SP.get();
        // END Transfer X to stack pointer

        // Transfer stack pointer to X

        mem[PC++] = cast(cpu6502::opcode::LDX::Immediate); // 2 cycles
        mem[PC++] = 0x33;
        cpu.execute(2);
        all_good &= cpu.get_registers().IRX.get() == 0x33;

        mem[PC++] = cast(cpu6502::opcode::TSX::Implied); // 2cycles
        cpu.execute(2);

        all_good = cpu.get_registers().IRX.get() == cpu.get_registers().SP.get()
                && cpu.get_registers().IRX.get() == 0x21;

        // END Transfer stack pointer to X

        // Push accumulator on stack
        mem[PC++] = cast(cpu6502::opcode::LDA::Immediate); // 2 cycles
        mem[PC++] = 0x33;
        cpu.execute(2);
        all_good &= cpu.get_registers().ACU.get() == 0x33;

        mem[PC++] = cast(cpu6502::opcode::PHA::Implied); // 3 cycles
        cpu.execute(3);
        all_good &= mem[cpu.get_registers().SP.get() + 1 + cpu6502::CPU::STACK_BEGIN] == 0x33;

        // END Push accumulator on stack

        // Pull accumulator from stack

        mem[PC++] = cast(cpu6502::opcode::LDA::Immediate); // 2 cycles
        mem[PC++] = 0x20;
        cpu.execute(2);
        all_good &= cpu.get_registers().ACU.get() == 0x20;

        mem[PC++] = cast(cpu6502::opcode::PLA::Implied); // 4 cycles
        cpu.execute(4);
        all_good &= cpu.get_registers().ACU.get() == 0x33;

        // END Pull accumulator from stack

        // Push processor status on stack

        mem[PC++] = cast(cpu6502::opcode::SEC::Implied); // 2 cycles
        mem[PC++] =  cast(cpu6502::opcode::SED::Implied); // 2 cycles
        mem[PC++] =  cast(cpu6502::opcode::SEI::Implied); // 2 cycles
        cpu.execute(6);
        all_good &= cpu.get_registers().PS.get(PSFlags::CarryFlag)
                && cpu.get_registers().PS.get(PSFlags::DecimalMode)
                && cpu.get_registers().PS.get(PSFlags::InterruptDisable);

        mem[PC++] = cast(cpu6502::opcode::PHP::Implied); // 3 cycles
        cpu.execute(3);
        auto PS = mem[cpu.get_registers().SP.get() + 1 + cpu6502::CPU::STACK_BEGIN];
        cpu6502::registers::ProcessorStatus ps;
        ps.put_byte(PS);
        all_good &= ps.get(PSFlags::CarryFlag)
                && ps.get(PSFlags::DecimalMode)
                && ps.get(PSFlags::InterruptDisable);

        // END Push processor status on stack

        // Pull processor status from stack

        mem[PC++] = cast(cpu6502::opcode::CLC::Implied); // 2 cycles
        mem[PC++] =  cast(cpu6502::opcode::CLD::Implied); // 2 cycles
        mem[PC++] =  cast(cpu6502::opcode::CLI::Implied); // 2 cycles
        cpu.execute(6);
        all_good &= !cpu.get_registers().PS.get(PSFlags::CarryFlag)
                    && !cpu.get_registers().PS.get(PSFlags::DecimalMode)
                    && !cpu.get_registers().PS.get(PSFlags::InterruptDisable);

        mem[PC++] = cast(cpu6502::opcode::PLP::Implied); // 4 cycles
        cpu.execute(4);
        all_good &= ps.get(PSFlags::CarryFlag)
                    && ps.get(PSFlags::DecimalMode)
                    && ps.get(PSFlags::InterruptDisable);

        // END Pull processor status from stack
        
        return all_good;
    }
}

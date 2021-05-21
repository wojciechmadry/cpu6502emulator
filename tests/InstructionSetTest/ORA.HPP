#ifndef cpu6502_TEST_ORA
#define cpu6502_TEST_ORA

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool ORA_TEST() noexcept
    {
        bool all_good = true;
        //using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        auto PC = cpu.get_registers().PC.get();
        auto cast = []<typename T>(const T Opcode) -> cpu6502::Byte
        {
            return static_cast<cpu6502::Byte>(Opcode);
        };

        mem[PC++]=cast(cpu6502::opcode::JMP::Absolute); // 3 cycles
        mem[PC++]=0x20;
        mem[PC++]=0x20;
        cpu.execute(3);
        PC = cpu.get_registers().PC.get();

        const cpu6502::Byte ACU = 0x33;
        const cpu6502::Byte IRX = 0x10;
        const cpu6502::Byte IRY = 0x15;
        const cpu6502::Byte ORA = 0xF0;
        const auto Res = ACU | ORA;

        auto LoadACU = [&]() mutable {
            mem[PC++]=cast(cpu6502::opcode::LDA::Immediate); // 2 cycles
            mem[PC++] = ACU;
            cpu.execute(2);
            all_good &= cpu.get_registers().ACU.get() == ACU;
        };

        auto LoadIRX = [&]() mutable {
            mem[PC++]=cast(cpu6502::opcode::LDX::Immediate); // 2 cycles
            mem[PC++] = IRX;
            cpu.execute(2);
            all_good &= cpu.get_registers().IRX.get() == IRX;
        };

        auto LoadIRY = [&]() mutable {
            mem[PC++]=cast(cpu6502::opcode::LDY::Immediate); // 2 cycles
            mem[PC++] = IRY;
            cpu.execute(2);
            all_good &= cpu.get_registers().IRY.get() == IRY;
        };
        LoadIRX();
        LoadIRY();
        LoadACU();

        // Immediate
        mem[PC++] = cast(cpu6502::opcode::ORA::Immediate); // 2 cycles
        mem[PC++] = ORA;
        cpu.execute(2);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END Immediate

        // ZeroPage
        mem[PC++] = cast(cpu6502::opcode::ORA::ZeroPage); // 3 cycles
        mem[PC++] = 0x11;
        mem[0x11] = ORA;
        cpu.execute(3);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END ZeroPage

        // ZeroPageX
        mem[PC++] = cast(cpu6502::opcode::ORA::ZeroPageX); // 4 cycles
        mem[PC++] = 0x11;
        mem[0x11+IRX] = ORA;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END ZeroPageX

        // Absolute
        mem[PC++] = cast(cpu6502::opcode::ORA::Absolute); // 4 cycles
        mem[PC++] = 0x30;
        mem[PC++] = 0x30;
        mem[0x3030] = ORA;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END Absolute

        // AbsoluteX
        mem[PC++] = cast(cpu6502::opcode::ORA::AbsoluteX); // 5 cycles
        mem[PC++] = 0x30;
        mem[PC++] = 0x30;
        mem[0x3030 + IRX] = ORA;
        cpu.execute(5);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END AbsoluteX

        // AbsoluteY
        mem[PC++] = cast(cpu6502::opcode::ORA::AbsoluteY); // 5 cycles
        mem[PC++] = 0x30;
        mem[PC++] = 0x30;
        mem[0x3030 + IRY] = ORA;
        cpu.execute(5);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END AbsoluteY

        // IndirectX
        mem[PC++] = cast(cpu6502::opcode::ORA::IndirectX); // 6 cycles
        mem[PC++] = 0x15;
        mem[0x15+IRX] = 0x33;
        mem[0x15+IRX+1] = 0x33;
        mem[0x3333] = ORA;
        cpu.execute(6);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        LoadACU();
        // END IndirectX

        // IndirectY
        mem[PC++] = cast(cpu6502::opcode::ORA::IndirectY); // 6 cycles
        mem[PC++] = 0x15;
        mem[0x15] = 0x35;
        mem[0x16] = 0x35;
        mem[0x3535 + IRY] = ORA;
        cpu.execute(6);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;
        // END IndirectY

        return all_good;
    }
}
#endif
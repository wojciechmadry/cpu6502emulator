#include "instruction_test.hpp"

#include "utility/utility.hpp"
#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool EOR_TEST()
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

        utils::jump_to_2020(cpu);
        PC = cpu.get_registers().PC.get();

        const cpu6502::Byte ACU = 0x33;
        const cpu6502::Byte IRX = 0x10;
        const cpu6502::Byte IRY = 0x15;
        const cpu6502::Byte EOR = 0xF0;
        const auto Res = ACU ^ EOR;

        utils::load_to_xreg(cpu, IRX) ;
        utils::load_to_yreg(cpu, IRY) ;
        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();

        // Immediate
        mem[PC++] = cast(cpu6502::opcode::EOR::Immediate); // 2 cycles
        mem[PC++] = EOR;
        cpu.execute(2);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END Immediate

        // ZeroPage
        mem[PC++] = cast(cpu6502::opcode::EOR::ZeroPage); // 3 cycles
        mem[PC++] = 0x11;
        mem[0x11] = EOR;
        cpu.execute(3);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END ZeroPage

        // ZeroPageX
        mem[PC++] = cast(cpu6502::opcode::EOR::ZeroPageX); // 4 cycles
        mem[PC++] = 0x11;
        mem[0x11+IRX] = EOR;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END ZeroPageX

        // Absolute
        mem[PC++] = cast(cpu6502::opcode::EOR::Absolute); // 4 cycles
        mem[PC++] = 0x30;
        mem[PC++] = 0x30;
        mem[0x3030] = EOR;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END Absolute

        // AbsoluteX
        mem[PC++] = cast(cpu6502::opcode::EOR::AbsoluteX); // 5 cycles
        mem[PC++] = 0x30;
        mem[PC++] = 0x30;
        mem[0x3030 + IRX] = EOR;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END AbsoluteX

        // AbsoluteY
        mem[PC++] = cast(cpu6502::opcode::EOR::AbsoluteY); // 5 cycles
        mem[PC++] = 0x30;
        mem[PC++] = 0x30;
        mem[0x3030 + IRY] = EOR;
        cpu.execute(4);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END AbsoluteY

        // IndirectX
        mem[PC++] = cast(cpu6502::opcode::EOR::IndirectX); // 6 cycles
        mem[PC++] = 0x15;
        mem[0x15+IRX] = 0x33;
        mem[0x15+IRX+1] = 0x33;
        mem[0x3333] = EOR;
        cpu.execute(6);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;

        utils::load_to_acu(cpu, ACU) ;
        PC = cpu.get_registers().PC.get();
        // END IndirectX

        // IndirectY
        mem[PC++] = cast(cpu6502::opcode::EOR::IndirectY); // 6 cycles
        mem[PC++] = 0x15;
        mem[0x15] = 0x35;
        mem[0x16] = 0x35;
        mem[0x3535 + IRY] = EOR;
        cpu.execute(5);

        all_good &= cpu.get_registers().ACU.get() != ACU
                    && cpu.get_registers().ACU.get() == Res;
        // END IndirectY

        return all_good;
    }
}
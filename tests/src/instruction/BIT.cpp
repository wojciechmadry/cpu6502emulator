#include "instruction_test.hpp"

#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool BIT_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
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

        cpu6502::Byte ACU = 0x33;
        cpu6502::Byte AND = 0xFF;
       // auto Res = ACU & AND;

        mem[PC++]=cast(cpu6502::opcode::LDA::Immediate); // 2 cycles
        mem[PC++] = ACU;

        cpu.execute(2);

        // ZERO_PAGE
        mem[PC++] = cast(cpu6502::opcode::BIT::ZeroPage); // 3 cycles
        mem[PC++] = 0x11;
        mem[0x11] = AND;
        cpu.execute(3);
        all_good &= cpu.get_registers().ACU.get() == ACU
                && cpu.get_registers().PS.get(PSFlags::OverflowFlag)
                && cpu.get_registers().PS.get(PSFlags::NegativeFlag)
                && !cpu.get_registers().PS.get(PSFlags::ZeroFlag);

        // END ZERO_PAGE

        // ABSOLUTE
        mem[PC++] = cast(cpu6502::opcode::BIT::Absolute); // 4 cycles
        mem[PC++] = 0x11;
        mem[PC++] = 0x11;
        mem[0x1111] = AND;
        cpu.execute(4);
        all_good &= cpu.get_registers().ACU.get() == ACU
                    && cpu.get_registers().PS.get(PSFlags::OverflowFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag)
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag);

        // END  ABSOLUTE
        return all_good;
    }
}
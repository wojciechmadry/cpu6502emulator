#include "cpu.hpp"

namespace cpu6502{
    void CPU::LDY() noexcept
    {
        using op = cpu6502::opcode::LDY;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };


        LookUpTable[cast(op::Immediate)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 1 cycles
            cpu.cpu_reg.IRY.set(cpu.fetch_byte(Cycles));
            // 0 cycles

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRY.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRY.get() & 0x80);
        };

        LookUpTable[cast(op::ZeroPage)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycles
            cpu.cpu_reg.IRY.set(cpu.read_byte(ZeroPageAddress, Cycles));
            // 0 cycles

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRY.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRY.get() & 0x80);
        };

        LookUpTable[cast(op::ZeroPageX)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 2 cycles
            ZeroPageAddress += cpu.cpu_reg.IRX.get();
            --Cycles;
            // 1 cycles
            cpu.cpu_reg.IRY.set(cpu.read_byte(ZeroPageAddress, Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRY.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRY.get() & 0x80);
        };

        LookUpTable[cast(op::Absolute)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 cycles
            Word address = cpu.fetch_word(Cycles);
            // 1 cycles
            cpu.cpu_reg.IRY.set(cpu.read_byte(address, Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRY.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRY.get() & 0x80);
        };

        LookUpTable[cast(op::AbsoluteX)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 4 cycles
            Word address = cpu.fetch_word(Cycles);
            // 2 cycles
            address += cpu.cpu_reg.IRX.get();
            if ( cpu.cpu_reg.IRX.get() != 0 )
                --Cycles; // 1 cycles if page crossed
            cpu.cpu_reg.IRY.set(cpu.read_byte(address, Cycles));
            // 0 cycles

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.IRY.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.IRY.get() & 0x80);
        };
    }
}
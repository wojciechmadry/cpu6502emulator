#include "cpu.hpp"

namespace cpu6502{
    void CPU::BIT() noexcept
    {
        using op = cpu6502::opcode::BIT;
        LookUpTable[static_cast<Byte>(op::ZeroPage)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycles
            Byte MemoryValue = cpu.read_byte(ZeroPageAddress, Cycles);
            // 0 Cycles;

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(MemoryValue & cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, MemoryValue & 0x80);
            cpu.cpu_reg.PS.set(PSFlags::OverflowFlag, MemoryValue & 0x40);
        };

        LookUpTable[static_cast<Byte>(op::Absolute)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 cycles
            Word address = cpu.fetch_word(Cycles);
            // 1 cycles
            Byte MemoryValue = cpu.read_byte(address, Cycles);
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(MemoryValue & cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, MemoryValue & 0x80);
            cpu.cpu_reg.PS.set(PSFlags::OverflowFlag, MemoryValue & 0x40);
        };
    }
}
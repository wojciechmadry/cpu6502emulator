#include "cpu.hpp"

namespace cpu6502{
    void CPU::BIT() noexcept
    {
        using op = cpu6502::opcode::BIT;
        LookUpTable[static_cast<Byte>(op::ZeroPage)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycles
            Byte TESTED = cpu.read_byte(ZeroPageAddress, Cycles) & cpu.cpu_reg.ACU.get();


            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(TESTED));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, TESTED & 0x80);
            cpu.cpu_reg.PS.set(PSFlags::OverflowFlag, TESTED & 0x40);
        };

        LookUpTable[static_cast<Byte>(op::Absolute)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 cycles
            Word address = cpu.fetch_word(Cycles);
            // 1 cycles
            Byte TESTED = cpu.read_byte(address, Cycles) & cpu.cpu_reg.ACU.get();
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(TESTED));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, TESTED & 0x80);
            cpu.cpu_reg.PS.set(PSFlags::OverflowFlag, TESTED & 0x40);
        };
    }
}
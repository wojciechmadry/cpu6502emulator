#include "cpu.hpp"

namespace cpu6502{

    void CPU::BITzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        Byte MemoryValue = read_byte(ZeroPageAddress, Cycles);
        // 0 Cycles;

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(MemoryValue & cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, MemoryValue & 0x80);
        cpu_reg.PS.set(PSFlags::OverflowFlag, MemoryValue & 0x40);
    }

    void CPU::BITabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        Word address = fetch_word(Cycles);
        // 1 cycles
        Byte MemoryValue = read_byte(address, Cycles);
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(MemoryValue & cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, MemoryValue & 0x80);
        cpu_reg.PS.set(PSFlags::OverflowFlag, MemoryValue & 0x40);
    }
    
}
#include "cpu.hpp"

namespace cpu6502{

    void CPU::BITzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched & cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
        cpu_reg.PS.set(PSFlags::OverflowFlag, fetched & 0x40);
    }

    void CPU::BITabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched & cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
        cpu_reg.PS.set(PSFlags::OverflowFlag, fetched & 0x40);
    }
    
}
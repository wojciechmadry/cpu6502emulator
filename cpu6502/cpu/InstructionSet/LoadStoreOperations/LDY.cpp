#include "cpu.hpp"

namespace cpu6502{

    void CPU::LDYimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        cpu_reg.IRY.set(fetched);
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDYzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        cpu_reg.IRY.set(fetched);
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDYzeropagex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
        cpu_reg.IRY.set(fetched);
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDYabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        cpu_reg.IRY.set(fetched);
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDYabsolutex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
        cpu_reg.IRY.set(fetched);
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

}

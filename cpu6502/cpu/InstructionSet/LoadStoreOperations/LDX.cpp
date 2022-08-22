#include "cpu.hpp"

namespace cpu6502 {

    void CPU::LDXimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        cpu_reg.IRX.set(fetched);
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDXzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        cpu_reg.IRX.set(fetched);
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched& 0x80);
    }

    void CPU::LDXzeropagey(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPageY>(Cycles);
        cpu_reg.IRX.set(fetched);
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDXabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        cpu_reg.IRX.set(fetched);
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

    void CPU::LDXabsolutey(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);
        cpu_reg.IRX.set(fetched);
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(fetched));
        cpu_reg.PS.set(PSFlags::NegativeFlag, fetched & 0x80);
    }

}

#include "cpu.hpp"
#include <limits>

namespace cpu6502{
    void CPU::SBCimmediate(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::Immediate>(Cycles));
        ADC(fetched);
    }

    void CPU::SBCzeropage(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::ZeroPage>(Cycles));
        ADC(fetched);
    }

    void CPU::SBCzeropagex(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::ZeroPageX>(Cycles));
        ADC(fetched);
    }

    void CPU::SBCabsolute(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::Absolute>(Cycles));
        ADC(fetched);
    }


    void CPU::SBCabsolutex(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::AbsoluteX>(Cycles));
        ADC(fetched);
    }


    void CPU::SBCabsolutey(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::AbsoluteY>(Cycles));
        ADC(fetched);
    }


    void CPU::SBCindirectx(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::IndirectX>(Cycles));
        ADC(fetched);
    }


    void CPU::SBCindirecty(u32& Cycles) noexcept
    {
        const auto fetched = static_cast<Byte>(~fetch<AddressingMode::IndirectY>(Cycles));
        ADC(fetched);
    }

}

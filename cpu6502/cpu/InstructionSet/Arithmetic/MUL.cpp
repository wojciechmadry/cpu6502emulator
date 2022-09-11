#include "cpu.hpp"

#include <type_traits>
#include <limits>

namespace cpu6502{

    void CPU::MUL(const Byte value) noexcept
    {
        auto& reg = cpu_reg;
        const auto ACU = reg.ACU.get();
        const auto word_data = static_cast<SByte>(value) * static_cast<SByte>(ACU);
        reg.ACU.set(static_cast<Byte>(word_data));
        
        reg.PS.set(CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0);
        reg.PS.set(CPU::PSFlags::NegativeFlag, reg.ACU.get() & 0x80);

        bool is_overflow = word_data < std::numeric_limits<SByte>::min() || word_data > std::numeric_limits<SByte>::max();
        reg.PS.set(CPU::PSFlags::OverflowFlag, is_overflow);
    }

    void CPU::MULimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        MUL(fetched);
    }

    void CPU::MULzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        MUL(fetched);
    }

    void CPU::MULzeropagex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
        MUL(fetched);
    }

    void CPU::MULabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        MUL(fetched);
    }


    void CPU::MULabsolutex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
        MUL(fetched);
    }


    void CPU::MULabsolutey(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);
        MUL(fetched);
    }


    void CPU::MULindirectx(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectX>(Cycles);
        MUL(fetched);
    }


    void CPU::MULindirecty(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectY>(Cycles);
        MUL(fetched);
    }
}

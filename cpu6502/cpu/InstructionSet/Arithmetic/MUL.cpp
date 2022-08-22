#include "cpu.hpp"

#include <limits>
#include <type_traits>

namespace cpu6502{

    void CPU::MUL(const Byte value) noexcept
    {
        // Overflow flag -> if ACU is treat as signed
        auto& reg = cpu_reg;
        const auto ACU = reg.ACU.get();
        const auto word_data = static_cast<Word>(value * ACU);
        reg.ACU.set(static_cast<Byte>(word_data));
        // 0 cycles
        
        reg.PS.set(CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0);
        reg.PS.set(CPU::PSFlags::NegativeFlag, reg.ACU.get() & 0x80);

        const auto signed_ACU = static_cast<SWord>(static_cast<SByte>(ACU));
        const auto signed_fetched = static_cast<SWord>(static_cast<SByte>(value));
        const auto signed_sum = signed_ACU * signed_fetched;
        reg.PS.set(CPU::PSFlags::OverflowFlag, signed_sum < std::numeric_limits<SByte>::min() || signed_sum > std::numeric_limits<SByte>::max());
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

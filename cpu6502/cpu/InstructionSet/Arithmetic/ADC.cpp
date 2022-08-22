#include "cpu.hpp"

#include <limits>
#include <type_traits>

namespace cpu6502{

    void CPU::ADC(const Byte value) noexcept
    {
        // Overflow flag -> if ACU is treat as signed
        // Carry flag -> if ACU is treat as unsigned
        auto& reg = cpu_reg;
        const auto ACU = reg.ACU.get();
        const auto carry_flag = reg.PS.get(CPU::PSFlags::CarryFlag);
        const auto word_data = static_cast<Word>(value + ACU + carry_flag);
        reg.ACU.set(static_cast<Byte>(word_data));
        // 0 cycles
        
        reg.PS.set(CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0);
        reg.PS.set(CPU::PSFlags::NegativeFlag, reg.ACU.get() & 0x80);

        const auto signed_ACU = static_cast<SWord>(static_cast<SByte>(ACU));
        const auto signed_fetched = static_cast<SWord>(static_cast<SByte>(value));
        const auto signed_sum = signed_ACU + signed_fetched + carry_flag;
        reg.PS.set(CPU::PSFlags::OverflowFlag, signed_sum < std::numeric_limits<SByte>::min() || signed_sum > std::numeric_limits<SByte>::max());
        reg.PS.set(CPU::PSFlags::CarryFlag, word_data > std::numeric_limits<Byte>::max());
    }

    void CPU::ADCimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        ADC(fetched);
    }

    void CPU::ADCzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        ADC(fetched);
    }

    void CPU::ADCzeropagex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
        ADC(fetched);
    }

    void CPU::ADCabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        ADC(fetched);
    }


    void CPU::ADCabsolutex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
        ADC(fetched);
    }


    void CPU::ADCabsolutey(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);
        ADC(fetched);
    }


    void CPU::ADCindirectx(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectX>(Cycles);
        ADC(fetched);
    }


    void CPU::ADCindirecty(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectY>(Cycles);
        ADC(fetched);
    }
}

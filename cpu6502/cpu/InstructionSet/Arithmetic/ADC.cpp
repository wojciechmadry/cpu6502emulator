#include "cpu.hpp"

#include <limits>

namespace cpu6502{
    void CPU::ADCimmediate(u32& Cycles) noexcept
    {
        // Overflow flag -> if ACU is treat as signed
        // Carry flag -> if ACU is treat as unsigned
        // 1 cycles
        const auto ACU = cpu_reg.ACU.get();
        const auto fetched = fetch_byte(Cycles);
        const auto word_data = static_cast<Word>(fetched + ACU + cpu_reg.PS.get(PSFlags::CarryFlag));
        cpu_reg.ACU.set(static_cast<Byte>(word_data));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, cpu_reg.ACU.get() == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);

        const auto signed_ACU = static_cast<SWord>(static_cast<SByte>(ACU));
        const auto signed_fetched = static_cast<SWord>(static_cast<SByte>(fetched));
        const auto signed_sum = signed_ACU + signed_fetched;
        cpu_reg.PS.set(PSFlags::OverflowFlag, signed_sum < std::numeric_limits<SByte>::min() || signed_sum > std::numeric_limits<SByte>::max());
        cpu_reg.PS.set(PSFlags::CarryFlag, word_data > std::numeric_limits<Byte>::max());
    }

    void CPU::ADCzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        (void) Cycles;
    }

    void CPU::ADCzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        (void) Cycles;
    }

    void CPU::ADCabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        (void) Cycles;
    }


    void CPU::ADCabsolutex(u32& Cycles) noexcept
    {
        // 3 cycles + 1 if page crossed
        (void) Cycles;
    }


    void CPU::ADCabsolutey(u32& Cycles) noexcept
    {
        // 3 cycles + 1 if page crossed
        (void) Cycles;
    }


    void CPU::ADCindirectx(u32& Cycles) noexcept
    {
        // 5 cycles
        (void) Cycles;
    }


    void CPU::ADCindirecty(u32& Cycles) noexcept
    {
        // 4 cycles + 1 if page crossed
        (void) Cycles;
    }
}
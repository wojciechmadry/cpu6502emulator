#include "cpu.hpp"

#include <limits>
#include <type_traits>

#include <iostream> // remove this
namespace cpu6502{

    template<typename INT1>
    requires(std::is_integral_v<INT1>)
    void add_to_acu(CPU& cpu, const INT1 value_to_add) noexcept
    {
        // Overflow flag -> if ACU is treat as signed
        // Carry flag -> if ACU is treat as unsigned
        auto& reg = cpu.get_registers();
        const auto ACU = reg.ACU.get();
        const auto carry_flag = reg.PS.get(CPU::PSFlags::CarryFlag);
        const auto word_data = static_cast<Word>(value_to_add + ACU + carry_flag);
        reg.ACU.set(static_cast<Byte>(word_data));
        // 0 cycles

        reg.PS.set(CPU::PSFlags::ZeroFlag, reg.ACU.get() == 0);
        reg.PS.set(CPU::PSFlags::NegativeFlag, reg.ACU.get() & 0x80);

        const auto signed_ACU = static_cast<SWord>(static_cast<SByte>(ACU));
        const auto signed_fetched = static_cast<SWord>(static_cast<SByte>(value_to_add));
        const auto signed_sum = signed_ACU + signed_fetched + carry_flag;
        reg.PS.set(CPU::PSFlags::OverflowFlag, signed_sum < std::numeric_limits<SByte>::min() || signed_sum > std::numeric_limits<SByte>::max());
        reg.PS.set(CPU::PSFlags::CarryFlag, word_data > std::numeric_limits<Byte>::max());
    }

    void CPU::ADCimmediate(u32& Cycles) noexcept
    {
        // 1 cycles
        const auto fetched = fetch_byte(Cycles);
        add_to_acu(*this, fetched);
        // 0 cycles
    }

    void CPU::ADCzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        const auto ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        const auto fetched = read_byte(ZeroPageAddress, Cycles);
        // 0 cycles
        add_to_acu(*this, fetched);
    }

    void CPU::ADCzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles;
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycles
        const auto fetched = read_byte(ZeroPageAddress, Cycles);
        // 0 cycles
        add_to_acu(*this, fetched);
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
#include "cpu.hpp"

#include <limits>
#include <type_traits>

#include <iostream> // remove this
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
        // 1 cycles
        const auto fetched = fetch_byte(Cycles);
        ADC(fetched);
        // 0 cycles
    }

    void CPU::ADCzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        const auto ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        const auto fetched = read_byte(ZeroPageAddress, Cycles);
        // 0 cycles
        ADC(fetched);
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
        ADC(fetched);
    }

    void CPU::ADCabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        const Word address = fetch_word(Cycles);
        // 1 cycles
        const auto fetched = read_byte(address, Cycles);
        // 0 cycles
        ADC(fetched);
    }


    void CPU::ADCabsolutex(u32& Cycles) noexcept
    {
        // 3 cycles + 1 if page crossed
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRX.get();
        if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
        const auto fetched = read_byte(address, Cycles);
        // 0 cycles
        ADC(fetched);
    }


    void CPU::ADCabsolutey(u32& Cycles) noexcept
    {
        // 3 cycles + 1 if page crossed
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRY.get();
        if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
        const auto fetched = read_byte(address, Cycles);
        // 0 cycles
        ADC(fetched);
    }


    void CPU::ADCindirectx(u32& Cycles) noexcept
    {
        // 5 cycles
        Byte address = fetch_byte(Cycles);
        // 4 cycles
        address += cpu_reg.IRX.get();
        --Cycles;
        // 3 cycles
        const Word TargetAddress = read_word(address, Cycles);
        // 1 cycles
        const auto fetched = read_byte(TargetAddress, Cycles);
        // 0 cycles
        ADC(fetched);
    }


    void CPU::ADCindirecty(u32& Cycles) noexcept
    {
        // 4 cycles + 1 if page crossed
        const Byte address = fetch_byte(Cycles);
        // 4 cycles
        Word TargetAddress = read_word(address, Cycles);
        // 2 cycles
        const auto OldAddress = TargetAddress;
        TargetAddress += cpu_reg.IRY.get();
        if ((TargetAddress >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed

        const auto fetched = read_byte(TargetAddress, Cycles);
        // 0 cycles

        ADC(fetched);
    }
}
#include "cpu.hpp"
#include <limits>

namespace cpu6502{
    void CPU::SBCimmediate(u32& Cycles) noexcept
    {
        // 1 cycles
        const auto fetched = static_cast<Byte>(~fetch_byte(Cycles));
        ADC(fetched);
    }

    void CPU::SBCzeropage(u32& Cycles) noexcept
    {
         // 2 cycles
        const auto ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        const auto fetched = static_cast<Byte>(~read_byte(ZeroPageAddress, Cycles));
        // 0 cycles
        ADC(fetched);
    }

    void CPU::SBCzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles;
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycles
        const auto fetched = static_cast<Byte>(~read_byte(ZeroPageAddress, Cycles));
        // 0 cycles
        ADC(fetched);
    }

    void CPU::SBCabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        const Word address = fetch_word(Cycles);
        // 1 cycles
        const auto fetched = static_cast<Byte>(~read_byte(address, Cycles));
        // 0 cycles
        ADC(fetched);
    }


    void CPU::SBCabsolutex(u32& Cycles) noexcept
    {
         // 3 cycles + 1 if page crossed
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRX.get();
        if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
        const auto fetched = static_cast<Byte>(~read_byte(address, Cycles));
        // 0 cycles
        ADC(fetched);
    }


    void CPU::SBCabsolutey(u32& Cycles) noexcept
    {
                // 3 cycles + 1 if page crossed
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRY.get();
        if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
        const auto fetched = static_cast<Byte>(~read_byte(address, Cycles));
        // 0 cycles
        ADC(fetched);
    }


    void CPU::SBCindirectx(u32& Cycles) noexcept
    {
        // 5 cycles
        Byte address = fetch_byte(Cycles);
        // 4 cycles
        address += cpu_reg.IRX.get();
        --Cycles;
        // 3 cycles
        const Word TargetAddress = read_word(address, Cycles);
        // 1 cycles
        const auto fetched = static_cast<Byte>(~read_byte(TargetAddress, Cycles));
        // 0 cycles
        ADC(fetched);
    }


    void CPU::SBCindirecty(u32& Cycles) noexcept
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

        const auto fetched = static_cast<Byte>(~read_byte(TargetAddress, Cycles));
        // 0 cycles

        ADC(fetched);
    }

}
#include "cpu.hpp"

namespace cpu6502{

    void CPU::LDYimmediate(u32& Cycles) noexcept
    {
        // 1 cycles
        cpu_reg.IRY.set(fetch_byte(Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
    }

    void CPU::LDYzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        const Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        cpu_reg.IRY.set(read_byte(ZeroPageAddress, Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
    }

    void CPU::LDYzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycles
        cpu_reg.IRY.set(read_byte(ZeroPageAddress, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
    }

    void CPU::LDYabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        const Word address = fetch_word(Cycles);
        // 1 cycles
        cpu_reg.IRY.set(read_byte(address, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
    }

    void CPU::LDYabsolutex(u32& Cycles) noexcept
    {
        // 4 cycles
        Word address = fetch_word(Cycles);
        // 2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRX.get();
        if ( (address >> 8) != (OldAddress>>8) )
            --Cycles; // 1 cycles if page crossed
        cpu_reg.IRY.set(read_byte(address, Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
    }

}
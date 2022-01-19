#include "cpu.hpp"

namespace cpu6502 {

    void CPU::LDXimmediate(u32& Cycles) noexcept
    {
        // 1 cycles
        cpu_reg.IRX.set(fetch_byte(Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
    }

    void CPU::LDXzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        cpu_reg.IRX.set(read_byte(ZeroPageAddress, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
    }

    void CPU::LDXzeropagey(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles
        ZeroPageAddress += cpu_reg.IRY.get();
        --Cycles;
        // 1 cycles
        cpu_reg.IRX.set(read_byte(ZeroPageAddress, Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
    }

    void CPU::LDXabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        Word address = fetch_word(Cycles);
        // 1 cycles
        cpu_reg.IRX.set(read_byte(address, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
    }

    void CPU::LDXabsolutey(u32& Cycles) noexcept
    {
        // 4 cycles
        Word address = fetch_word(Cycles);
        // 2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRY.get();
        if ((address >> 8) != (OldAddress>>8))
            --Cycles;  // 1 cycles if page crossed
        cpu_reg.IRX.set(read_byte(address, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRX.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRX.get() & 0x80);
    }

}
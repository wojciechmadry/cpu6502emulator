#include "cpu.hpp"

namespace cpu6502{

    void CPU::LSRaccumulator(u32& Cycles) noexcept
    {
        // 1 cycles
        const auto ACU = cpu_reg.ACU.get();
        const auto old_zero_bit = static_cast<bool>(ACU & 0x1);
        const auto shifted = static_cast<Byte>( ACU >> 1);
        const auto new_seventh_bit = static_cast<bool>(shifted & 0x80);;
        --Cycles;
        cpu_reg.ACU.set(shifted);
        // 0 cycles

        cpu_reg.PS.set(PSFlags::CarryFlag, old_zero_bit);
        cpu_reg.PS.set(PSFlags::ZeroFlag, shifted == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, new_seventh_bit);
    }

    void CPU::LSRzeropage(u32& Cycles) noexcept
    {
        const auto ZeroPageAddress = fetch_byte(Cycles);
        const auto fetched = read_byte(ZeroPageAddress, Cycles);
        const auto shifted = static_cast<Byte>(fetched >> 1);
        --Cycles;
        write_byte(shifted, ZeroPageAddress, Cycles);

        const auto old_zero_bit = static_cast<bool>(fetched & 0x1);
        const auto new_seventh_bit = static_cast<bool>(shifted & 0x80);

        cpu_reg.PS.set(PSFlags::CarryFlag, old_zero_bit);
        cpu_reg.PS.set(PSFlags::ZeroFlag, shifted == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, new_seventh_bit);
    }
 
    void CPU::LSRzeropagex(u32& Cycles) noexcept
    {
        // 5 cycles
        auto ZeroPageAddress = fetch_byte(Cycles);
        // 4 cycles
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 3 cycles
        const auto fetched = read_byte(ZeroPageAddress, Cycles);
        const auto shifted = static_cast<Byte>(fetched >> 1);
        --Cycles;
        // 1 cycles
        write_byte(shifted, ZeroPageAddress, Cycles);
        // 0 cycles

        const auto old_zero_bit = static_cast<bool>(fetched & 0x1);
        const auto new_seventh_bit = static_cast<bool>(shifted & 0x80);;

        cpu_reg.PS.set(PSFlags::CarryFlag, old_zero_bit);
        cpu_reg.PS.set(PSFlags::ZeroFlag, shifted == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, new_seventh_bit);
    }
 
    void CPU::LSRabsolute(u32& Cycles) noexcept
    {
        // 5 cycles
        const Word address = fetch_word(Cycles);
        // 3 cycles
        const auto fetched = read_byte(address, Cycles);
        // 2 cycles
        const auto shifted = static_cast<Byte>(fetched >> 1);
        --Cycles;
        // 1 cycles
        write_byte(shifted, address, Cycles);
        // 0 cycles

        const auto old_zero_bit = static_cast<bool>(fetched & 0x1);
        const auto new_seventh_bit = static_cast<bool>(shifted & 0x80);;

        cpu_reg.PS.set(PSFlags::CarryFlag, old_zero_bit);
        cpu_reg.PS.set(PSFlags::ZeroFlag, shifted == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, new_seventh_bit);
    }
    
    void CPU::LSRabsolutex(u32& Cycles) noexcept
    {
        // 6 cycles
        Word address = fetch_word(Cycles);
        // 4 cycles
        address += cpu_reg.IRX.get();
        --Cycles;
        // 3 cycles
        const auto fetched = read_byte(address, Cycles);
        // 2 cycles
        const auto shifted = static_cast<Byte>(fetched >> 1);
        --Cycles;
        // 1 cycles
        write_byte(shifted, address, Cycles);
        // 0 cycles

        const auto old_zero_bit = static_cast<bool>(fetched & 0x1);
        const auto new_seventh_bit = static_cast<bool>(shifted & 0x80);;

        cpu_reg.PS.set(PSFlags::CarryFlag, old_zero_bit);
        cpu_reg.PS.set(PSFlags::ZeroFlag, shifted == 0);
        cpu_reg.PS.set(PSFlags::NegativeFlag, new_seventh_bit);
    }
 
}
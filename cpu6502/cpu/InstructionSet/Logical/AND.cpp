#include "cpu.hpp"

namespace cpu6502{

    void CPU::ANDimmediate(u32& Cycles) noexcept
    {
        //1 Cycles
        cpu_reg.ACU.set( fetch_byte(Cycles) & cpu_reg.ACU.get());
        //0 Cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::ANDzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        const Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(ZeroPageAddress, Cycles));
        // 0 cycles
        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

    
    void CPU::ANDzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycles
        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(ZeroPageAddress, Cycles));
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
        
    }    


    void CPU::ANDabsolute(u32& Cycles) noexcept
    {
        // 3 Cycles
        const Word address = fetch_word(Cycles);
        // 1 cycles
        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(address, Cycles));
        // 0 Cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

    void CPU::ANDabsolutex(u32& Cycles) noexcept
    {
        // 4 cycles
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRX.get();
        if ((address >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed
        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(address, Cycles));
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }      

    void CPU::ANDabsolutey(u32& Cycles) noexcept
    {
        // 4 cycles
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRY.get();
        if ((address >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed
        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(address, Cycles));
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }      

    void CPU::ANDindirectx(u32& Cycles) noexcept
    {
        // 5 cycles
        Byte address = fetch_byte(Cycles);
        // 4 cycles
        address += cpu_reg.IRX.get();
        --Cycles;
        // 3 cycles
        const Word TargetAddress = read_word(address, Cycles);
        // 1 cycles
        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(TargetAddress, Cycles));
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  

    void CPU::ANDindirecty(u32& Cycles) noexcept
    {
        // 5 cycles
        const Byte address = fetch_byte(Cycles);
        // 4 cycles
        Word TargetAddress = read_word(address, Cycles);
        // 2 cycles
        const auto OldAddress = TargetAddress;
        TargetAddress += cpu_reg.IRY.get();
        if ((TargetAddress >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed

        cpu_reg.ACU.set(cpu_reg.ACU.get() & read_byte(TargetAddress, Cycles));
        // 0 cycles

        //Flag set
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }  
 
}
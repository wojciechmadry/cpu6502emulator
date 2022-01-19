#include "cpu.hpp"

namespace cpu6502{


    void CPU::STAzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycle
        write_byte(cpu_reg.ACU.get(), ZeroPageAddress, Cycles);
        // 0 cycles
    }

    void CPU::STAzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycle
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycle
        write_byte(cpu_reg.ACU.get(), ZeroPageAddress, Cycles);
        // 0 cycles
    }

    void CPU::STAabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        Word Address = fetch_word(Cycles);
        // 1 cycle
        write_byte(cpu_reg.ACU.get(), Address, Cycles);
        // 0 cycles
    }

    void CPU::STAabsolutex(u32& Cycles) noexcept
    {
        // 4 cycles
        Word Address = fetch_word(Cycles);
        // 2 cycle
        Address += cpu_reg.IRX.get();
        --Cycles;
        //1 Cycles
        write_byte(cpu_reg.ACU.get(), Address, Cycles);
        // 0 cycles
    }

    void CPU::STAabsolutey(u32& Cycles) noexcept
    {
        // 4 cycles
        Word Address = fetch_word(Cycles);
        // 2 cycle
        Address += cpu_reg.IRY.get();
        --Cycles;
        //1 Cycles
        write_byte(cpu_reg.ACU.get(), Address, Cycles);
        // 0 cycles
    }

    void CPU::STAindirectx(u32& Cycles) noexcept
    {
        // 5 cycles
        Byte address = fetch_byte(Cycles);
        // 4 cycles
        address += cpu_reg.IRX.get();
        --Cycles;
        //3 cycles
        Word TargetAddress = read_word(address, Cycles);
        //1 cycles
        write_byte(cpu_reg.ACU.get(), TargetAddress, Cycles);
        // 0 cycles
    }

    void CPU::STAindirecty(u32& Cycles) noexcept
    {
        // 5 cycles
        Byte address = fetch_byte(Cycles);
        // 4 cycles
        address += cpu_reg.IRY.get();
        --Cycles;
        //3 cycles
        Word TargetAddress = read_word(address, Cycles);
        //1 cycles
        write_byte(cpu_reg.ACU.get(), TargetAddress, Cycles);
        // 0 cycles
    }

}
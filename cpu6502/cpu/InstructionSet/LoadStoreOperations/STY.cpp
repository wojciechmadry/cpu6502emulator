#include "cpu.hpp"

namespace cpu6502{

    void CPU::STYzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycle
        write_byte(cpu_reg.IRY.get(), ZeroPageAddress, Cycles);
        // 0 cycles
    }

    void CPU::STYzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycle
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycle
        write_byte(cpu_reg.IRY.get(), ZeroPageAddress, Cycles);
        // 0 cycles
    }

    void CPU::STYabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        Word Address = fetch_word(Cycles);
        // 1 cycle
        write_byte(cpu_reg.IRY.get(), Address, Cycles);
        // 0 cycles
    }
    
}
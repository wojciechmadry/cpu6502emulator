#include "cpu.hpp"

namespace cpu6502{

    void CPU::STXzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        const Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycle
        write_byte(cpu_reg.IRX.get(), ZeroPageAddress, Cycles);
        // 0 cycles
    }

    void CPU::STXzeropagey(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycle
        ZeroPageAddress += cpu_reg.IRY.get();
        --Cycles;
        // 1 cycle
        write_byte(cpu_reg.IRX.get(), ZeroPageAddress, Cycles);
        // 0 cycles
    }

    void CPU::STXabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        const Word Address = fetch_word(Cycles);
        // 1 cycle
        write_byte(cpu_reg.IRX.get(), Address, Cycles);
        // 0 cycles
    }

}

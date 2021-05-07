#include "cpu.hpp"

namespace cpu6502{
    void CPU::STY() noexcept
    {
        using op = cpu6502::opcode::STY;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::ZeroPage)] = [this](u32& Cycles) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = fetch_byte(Cycles);
            // 1 cycle
            write_byte(cpu_reg.IRY.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::ZeroPageX)] = [this](u32& Cycles) -> void
        {
            // 3 cycles
            Byte ZeroPageAddress = fetch_byte(Cycles);
            // 2 cycle
            ZeroPageAddress += cpu_reg.IRX.get();
            --Cycles;
            // 1 cycle
            write_byte(cpu_reg.IRY.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::Absolute)] = [this](u32& Cycles) -> void
        {
            // 3 cycles
            Word Address = fetch_word(Cycles);
            // 1 cycle
            write_byte(cpu_reg.IRY.get(), Address, Cycles);
            // 0 cycles
        };

    }
}
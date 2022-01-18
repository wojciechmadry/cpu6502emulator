#include "cpu.hpp"

namespace cpu6502{

    void CPU::STXzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
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
        Word Address = fetch_word(Cycles);
        // 1 cycle
        write_byte(cpu_reg.IRX.get(), Address, Cycles);
        // 0 cycles
    }

    // remove this
    /*
    void CPU::STX() noexcept
    {
        using op = cpu6502::opcode::STX;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::ZeroPage)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycle
            cpu.write_byte(cpu.cpu_reg.IRX.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::ZeroPageY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 3 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 2 cycle
            ZeroPageAddress += cpu.cpu_reg.IRY.get();
            --Cycles;
            // 1 cycle
            cpu.write_byte(cpu.cpu_reg.IRX.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 3 cycles
            Word Address = cpu.fetch_word(Cycles);
            // 1 cycle
            cpu.write_byte(cpu.cpu_reg.IRX.get(), Address, Cycles);
            // 0 cycles
        };

    }*/
}
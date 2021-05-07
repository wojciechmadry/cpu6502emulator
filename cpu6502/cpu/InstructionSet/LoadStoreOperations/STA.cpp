#include "cpu.hpp"

namespace cpu6502{
    void CPU::STA() noexcept
    {
        using op = cpu6502::opcode::STA;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::ZeroPage)] = [this](u32& Cycles) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = fetch_byte(Cycles);
            // 1 cycle
            write_byte(cpu_reg.ACU.get(), ZeroPageAddress, Cycles);
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
            write_byte(cpu_reg.ACU.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::Absolute)] = [this](u32& Cycles) -> void
        {
            // 3 cycles
            Word Address = fetch_word(Cycles);
            // 1 cycle
            write_byte(cpu_reg.ACU.get(), Address, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::AbsoluteX)] = [this](u32& Cycles) -> void
        {
            // 4 cycles
            Word Address = fetch_word(Cycles);
            // 2 cycle
            Address += cpu_reg.IRX.get();
            --Cycles;
            //1 Cycles
            write_byte(cpu_reg.ACU.get(), Address, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::AbsoluteY)] = [this](u32& Cycles) -> void
        {
            // 4 cycles
            Word Address = fetch_word(Cycles);
            // 2 cycle
            Address += cpu_reg.IRY.get();
            --Cycles;
            //1 Cycles
            write_byte(cpu_reg.ACU.get(), Address, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::IndircetX)] = [this](u32& Cycles) -> void
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
        };

        LookUpTable[cast(op::IndircetY)] = [this](u32& Cycles) -> void
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
        };
    }
}
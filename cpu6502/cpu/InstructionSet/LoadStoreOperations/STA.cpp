#include "cpu.hpp"

namespace cpu6502{
    void CPU::STA() noexcept
    {
        using op = cpu6502::opcode::STA;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::ZeroPage)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycle
            cpu.write_byte(cpu.cpu_reg.ACU.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::ZeroPageX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 3 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 2 cycle
            ZeroPageAddress += cpu.cpu_reg.IRX.get();
            --Cycles;
            // 1 cycle
            cpu.write_byte(cpu.cpu_reg.ACU.get(), ZeroPageAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 3 cycles
            Word Address = cpu.fetch_word(Cycles);
            // 1 cycle
            cpu.write_byte(cpu.cpu_reg.ACU.get(), Address, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::AbsoluteX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 4 cycles
            Word Address = cpu.fetch_word(Cycles);
            // 2 cycle
            Address += cpu.cpu_reg.IRX.get();
            --Cycles;
            //1 Cycles
            cpu.write_byte(cpu.cpu_reg.ACU.get(), Address, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::AbsoluteY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 4 cycles
            Word Address = cpu.fetch_word(Cycles);
            // 2 cycle
            Address += cpu.cpu_reg.IRY.get();
            --Cycles;
            //1 Cycles
            cpu.write_byte(cpu.cpu_reg.ACU.get(), Address, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::IndircetX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 5 cycles
            Byte address = cpu.fetch_byte(Cycles);
            // 4 cycles
            address += cpu.cpu_reg.IRX.get();
            --Cycles;
            //3 cycles
            Word TargetAddress = cpu.read_word(address, Cycles);
            //1 cycles
            cpu.write_byte(cpu.cpu_reg.ACU.get(), TargetAddress, Cycles);
            // 0 cycles
        };

        LookUpTable[cast(op::IndircetY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 5 cycles
            Byte address = cpu.fetch_byte(Cycles);
            // 4 cycles
            address += cpu.cpu_reg.IRY.get();
            --Cycles;
            //3 cycles
            Word TargetAddress = cpu.read_word(address, Cycles);
            //1 cycles
            cpu.write_byte(cpu.cpu_reg.ACU.get(), TargetAddress, Cycles);
            // 0 cycles
        };
    }
}
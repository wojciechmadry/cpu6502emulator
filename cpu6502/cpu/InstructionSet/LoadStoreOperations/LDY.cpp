#include "cpu.hpp"

namespace cpu6502 {
    void CPU::LDY() noexcept
    {
        using op = cpu6502::opcode::LDY;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        auto InitFlag = [this]()->void{
            cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.IRY.get()));
            cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.IRY.get() & 0x80);
        };


        LookUpTable[cast(op::Immediate)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 1 cycles
            cpu_reg.IRY.set(fetch_byte(Cycles));
            // 0 cycles

            InitFlag();
        };

        LookUpTable[cast(op::ZeroPage)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = fetch_byte(Cycles);
            // 1 cycles
            cpu_reg.IRY.set(read_byte(ZeroPageAddress, Cycles));
            // 0 cycles

            InitFlag();
        };

        LookUpTable[cast(op::ZeroPageX)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 3 cycles
            Byte ZeroPageAddress = fetch_byte(Cycles);
            // 2 cycles
            ZeroPageAddress += cpu_reg.IRX.get();
            --Cycles;
            // 1 cycles
            cpu_reg.IRY.set(read_byte(ZeroPageAddress, Cycles));
            // 0 cycles
            InitFlag();
        };

        LookUpTable[cast(op::Absolute)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 3 cycles
            Word address = fetch_word(Cycles);
            // 1 cycles
            cpu_reg.IRY.set(read_byte(address, Cycles));
            // 0 cycles
            InitFlag();
        };

        LookUpTable[cast(op::AbsoluteX)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 4 cycles
            Word address = fetch_word(Cycles);
            // 2 cycles
            address += cpu_reg.IRX.get();
            if (cpu_reg.IRX.get() != 0)
                --Cycles; // 1 cycles if page crossed
            cpu_reg.IRY.set(read_byte(address, Cycles));
            // 0 cycles

            InitFlag();
        };
    }
}
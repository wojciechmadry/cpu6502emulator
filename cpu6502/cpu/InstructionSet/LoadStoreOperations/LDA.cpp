#include "cpu.hpp"

namespace cpu6502 {
    void CPU::LDA() noexcept {
        using op = cpu6502::opcode::LDA;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        auto InitFlag = [this]()->void{
            cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
            cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[cast(op::Immediate)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 1 cycles
            cpu_reg.ACU.set(fetch_byte(Cycles));
            // 0 cycles
            InitFlag();
        };


        LookUpTable[cast(op::ZeroPage)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = fetch_byte(Cycles);
            // 1 cycles
            cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));
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
            cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));
            // 0 cycles

            InitFlag();
        };

        LookUpTable[cast(op::Absolute)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 3 cycles
            Word address = fetch_word(Cycles);
            // 1 cycles
            cpu_reg.ACU.set(read_byte(address, Cycles));
            // 0 cycles
            InitFlag();
        };

        LookUpTable[cast(op::AbsoluteX)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 4 cycles
            Word address = fetch_word(Cycles);
            //2 cycles
            address += cpu_reg.IRX.get();
            if (cpu_reg.IRX.get() != 0)
                --Cycles; // 1 cycles if page crossed
            cpu_reg.ACU.set(read_byte(address, Cycles));
            // 0 cycles
            InitFlag();
        };

        LookUpTable[cast(op::AbsoluteY)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 4 cycles
            Word address = fetch_word(Cycles);
            //2 cycles
            address += cpu_reg.IRY.get();
            if (cpu_reg.IRY.get() != 0)
                --Cycles; // 1 cycles if page crossed
            cpu_reg.ACU.set(read_byte(address, Cycles));
            // 0 cycles
            InitFlag();
        };

        LookUpTable[cast(op::IndirectX)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 5 cycles
            Byte address = fetch_byte(Cycles);
            // 4 cycles
            address += cpu_reg.IRX.get();
            --Cycles;
            // 3 cycles
            Word TargetAddress = read_word(address, Cycles);
            // 1 cycles
            cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));
            // 0 cycles

            InitFlag();
        };

        LookUpTable[cast(op::IndirectY)] = [this, InitFlag](u32& Cycles) -> void
        {
            // 5 cycles
            Byte address = fetch_byte(Cycles);
            // 4 cycles
            Word TargetAddress = read_word(address, Cycles);
            // 2 cycles
            TargetAddress += cpu_reg.IRY.get();
            if (cpu_reg.IRY.get() != 0)
                --Cycles; // 1 cycles if page crossed

            cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));
            // 0 cycles

            InitFlag();
        };

    }
}

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

            cpu_reg.ACU.set(fetch_byte(Cycles));

            InitFlag();
        };


        LookUpTable[cast(op::ZeroPage)] = [this, InitFlag](u32& Cycles) -> void
        {
            Byte ZeroPageAddress = fetch_byte(Cycles);
            cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));

            InitFlag();

        };

        LookUpTable[cast(op::ZeroPageX)] = [this, InitFlag](u32& Cycles) -> void
        {
            Byte ZeroPageAddress = fetch_byte(Cycles);
            ZeroPageAddress += cpu_reg.IRX.get();
            --Cycles;
            cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));

            InitFlag();
        };

        LookUpTable[cast(op::Absolute)] = [this, InitFlag](u32& Cycles) -> void
        {
            Word address = fetch_word(Cycles);
            cpu_reg.ACU.set(read_byte(address, Cycles));
            InitFlag();
        };

        LookUpTable[cast(op::AbsoluteX)] = [this, InitFlag](u32& Cycles) -> void
        {
            Word address = fetch_word(Cycles);
            address += cpu_reg.IRX.get();
            if (cpu_reg.IRX.get() != 0)
                --Cycles;
            cpu_reg.ACU.set(read_byte(address, Cycles));

            InitFlag();
        };

        LookUpTable[cast(op::AbsoluteY)] = [this, InitFlag](u32& Cycles) -> void
        {
            Word address = fetch_word(Cycles);
            address += cpu_reg.IRY.get();
            if (cpu_reg.IRY.get() != 0)
                --Cycles;
            cpu_reg.ACU.set(read_byte(address, Cycles));

            InitFlag();
        };

        LookUpTable[cast(op::IndirectX)] = [this, InitFlag](u32& Cycles) -> void
        {
            Byte address = fetch_byte(Cycles);
            address += cpu_reg.IRX.get();
            --Cycles;
            Word TargetAddress = read_word(address, Cycles);
            cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));

            InitFlag();
        };

        LookUpTable[cast(op::IndirectY)] = [this, InitFlag](u32& Cycles) -> void
        {
            Byte address = fetch_byte(Cycles);
            Word TargetAddress = read_word(address, Cycles);
            TargetAddress += cpu_reg.IRY.get();
            if (cpu_reg.IRY.get() != 0)
                --Cycles;
            cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));

            InitFlag();
        };

    }
}

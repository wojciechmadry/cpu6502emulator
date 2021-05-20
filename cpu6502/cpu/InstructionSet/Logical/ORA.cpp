#include "cpu.hpp"

namespace cpu6502{
    void CPU::ORA() noexcept
    {
        using op = cpu6502::opcode::ORA;
        LookUpTable[static_cast<Byte>(op::Immediate)] = [](u32 &Cycles, CPU &cpu) -> void {
            //1 Cycles
            cpu.cpu_reg.ACU.set(cpu.fetch_byte(Cycles) | cpu.cpu_reg.ACU.get());
            //0 Cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::ZeroPage)] = [](u32 &Cycles, CPU &cpu) -> void {

            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(ZeroPageAddress, Cycles));
            // 0 cycles
            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::ZeroPageX)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 2 cycles
            ZeroPageAddress += cpu.cpu_reg.IRX.get();
            --Cycles;
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(ZeroPageAddress, Cycles));
            // 0 cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::Absolute)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 Cycles
            Word address = cpu.fetch_word(Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(address, Cycles));
            // 0 Cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::AbsoluteX)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 4 cycles
            Word address = cpu.fetch_word(Cycles);
            //2 cycles
            address += cpu.cpu_reg.IRX.get();
            if (cpu.cpu_reg.IRX.get() != 0)
                --Cycles; // 1 cycles if page crossed
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(address, Cycles));
            // 0 cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::AbsoluteY)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 4 cycles
            Word address = cpu.fetch_word(Cycles);
            //2 cycles
            address += cpu.cpu_reg.IRY.get();
            if (cpu.cpu_reg.IRY.get() != 0)
                --Cycles; // 1 cycles if page crossed
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(address, Cycles));
            // 0 cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::IndirectX)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 5 cycles
            Byte address = cpu.fetch_byte(Cycles);
            // 4 cycles
            address += cpu.cpu_reg.IRX.get();
            --Cycles;
            // 3 cycles
            Word TargetAddress = cpu.read_word(address, Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(TargetAddress, Cycles));
            // 0 cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[static_cast<Byte>(op::IndirectY)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 5 cycles
            Byte address = cpu.fetch_byte(Cycles);
            // 4 cycles
            Word TargetAddress = cpu.read_word(address, Cycles);
            // 2 cycles
            TargetAddress += cpu.cpu_reg.IRY.get();
            if (cpu.cpu_reg.IRY.get() != 0)
                --Cycles; // 1 cycles if page crossed

            cpu.cpu_reg.ACU.set(cpu.cpu_reg.ACU.get() | cpu.read_byte(TargetAddress, Cycles));
            // 0 cycles

            //Flag set
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };
    }
}
#include "cpu.hpp"

namespace cpu6502 {

    void CPU::LDAimmediate(u32& Cycles) noexcept
    {
        // 1 cycles
        cpu_reg.ACU.set(fetch_byte(Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::LDAzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);

    }

    void CPU::LDAzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycles
        cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::LDAabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        Word address = fetch_word(Cycles);
        // 1 cycles
        cpu_reg.ACU.set(read_byte(address, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::LDAabsolutex(u32& Cycles) noexcept
    {
        // 4 cycles
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRX.get();
        if ((address >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed
        cpu_reg.ACU.set(read_byte(address, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::LDAabsolutey(u32& Cycles) noexcept
    {
        // 4 cycles
        Word address = fetch_word(Cycles);
        //2 cycles
        const auto OldAddress = address;
        address += cpu_reg.IRY.get();
        if ((address >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed
        cpu_reg.ACU.set(read_byte(address, Cycles));
        // 0 cycles
        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::LDAindirectx(u32& Cycles) noexcept
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

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    void CPU::LDAindirecty(u32& Cycles) noexcept
    {
        // 5 cycles
        Byte address = fetch_byte(Cycles);
        // 4 cycles
        Word TargetAddress = read_word(address, Cycles);
        // 2 cycles
        const auto OldAddress = TargetAddress;
        TargetAddress += cpu_reg.IRY.get();
        if ((TargetAddress >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed

        cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));
        // 0 cycles

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);
    }

    // remove this
    /*
    void CPU::LDA() noexcept {
        using op = cpu6502::opcode::LDA;

        auto cast = [](op Opcode) -> Byte {
            return static_cast<Byte>(Opcode);
        };

        LookUpTable[cast(op::Immediate)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.fetch_byte(Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };


        LookUpTable[cast(op::ZeroPage)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 2 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.read_byte(ZeroPageAddress, Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);

        };

        LookUpTable[cast(op::ZeroPageX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 3 cycles
            Byte ZeroPageAddress = cpu.fetch_byte(Cycles);
            // 2 cycles
            ZeroPageAddress += cpu.cpu_reg.IRX.get();
            --Cycles;
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.read_byte(ZeroPageAddress, Cycles));
            // 0 cycles

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[cast(op::Absolute)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 3 cycles
            Word address = cpu.fetch_word(Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.read_byte(address, Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[cast(op::AbsoluteX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 4 cycles
            Word address = cpu.fetch_word(Cycles);
            //2 cycles
            const auto OldAddress = address;
            address += cpu.cpu_reg.IRX.get();
            if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
            cpu.cpu_reg.ACU.set(cpu.read_byte(address, Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[cast(op::AbsoluteY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 4 cycles
            Word address = cpu.fetch_word(Cycles);
            //2 cycles
            const auto OldAddress = address;
            address += cpu.cpu_reg.IRY.get();
            if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
            cpu.cpu_reg.ACU.set(cpu.read_byte(address, Cycles));
            // 0 cycles
            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[cast(op::IndirectX)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 5 cycles
            Byte address = cpu.fetch_byte(Cycles);
            // 4 cycles
            address += cpu.cpu_reg.IRX.get();
            --Cycles;
            // 3 cycles
            Word TargetAddress = cpu.read_word(address, Cycles);
            // 1 cycles
            cpu.cpu_reg.ACU.set(cpu.read_byte(TargetAddress, Cycles));
            // 0 cycles

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

        LookUpTable[cast(op::IndirectY)] = [](u32& Cycles, CPU& cpu) -> void
        {
            // 5 cycles
            Byte address = cpu.fetch_byte(Cycles);
            // 4 cycles
            Word TargetAddress = cpu.read_word(address, Cycles);
            // 2 cycles
            const auto OldAddress = TargetAddress;
            TargetAddress += cpu.cpu_reg.IRY.get();
            if ((TargetAddress >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed

            cpu.cpu_reg.ACU.set(cpu.read_byte(TargetAddress, Cycles));
            // 0 cycles

            cpu.cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu.cpu_reg.ACU.get()));
            cpu.cpu_reg.PS.set(PSFlags::NegativeFlag, cpu.cpu_reg.ACU.get() & 0x80);
        };

    }*/
}

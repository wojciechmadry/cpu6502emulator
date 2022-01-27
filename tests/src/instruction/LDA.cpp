#include "instruction_test.hpp"

#include "cpu.hpp"

namespace CPU6502_TEST::inner{
    bool LDA_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        auto p = PSFlags::BreakCommand;
        (void)p;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;


        auto PC = cpu.get_registers().PC.get();
        mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute);
        mem[PC++] = 0x20;
        mem[PC++] = 0x20;

        PC = cpu.get_registers().PC.get();

        //ASSERT LDA - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::Immediate);

        mem[PC++] = opcode;
        mem[PC++] = 40;
        cpu.execute(2);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0;
        cpu.execute(2);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 128;
        cpu.execute(2);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Immediate

//ASSERT LDA - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::ZeroPage);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));


        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(3);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(3);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Zero Page


        //ASSERT LDA - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::ZeroPageX);

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Zero Page X

        //ASSERT LDA - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::Absolute);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Absolute

        //ASSERT LDA - Absolute X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::AbsoluteX);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Absolute X

        //ASSERT LDA - Absolute Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::AbsoluteY);

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x41;
        mem[PC++] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Absolute Y


        //ASSERT LDA - Indirect X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::IndirectX);

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(6);
        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(6);
        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(6);

        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Indirect X

        //ASSERT LDA - Indirect Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::IndirectY);

        mem[PC++] = opcode;
        mem[PC++] = 0x86;
        mem[0x86] = 0x28;
        mem[0x87] = 0x40;
        mem[0x4028] = 40;
        cpu.execute(5);
        all_good &=(cpu.get_registers().ACU.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x86;
        mem[0x86] = 0x28;
        mem[0x87] = 0x40;
        mem[0x4028] = 0x0;
        cpu.execute(5);
        all_good &=(cpu.get_registers().ACU.get() == 0
                    && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        mem[PC++] = opcode;
        mem[PC++] = 0x86;
        mem[0x86] = 0x28;
        mem[0x87] = 0x40;
        mem[0x4028] = 128;
        cpu.execute(5);
        all_good &=(cpu.get_registers().ACU.get() == 128
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Indirect Y
        return all_good;
    }
}
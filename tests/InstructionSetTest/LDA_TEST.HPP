#ifndef cpu6502_TEST_LDA
#define cpu6502_TEST_LDA

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool LDA_TEST() noexcept
    {

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;
        //ASSERT LDA - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::Immediate);
        cpu.reset();
        auto PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 40;
        cpu.execute(2);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0;
        cpu.execute(2);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 128;
        cpu.execute(2);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Immediate

//ASSERT LDA - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::ZeroPage);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(3);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(3);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Zero Page


        //ASSERT LDA - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::ZeroPageX);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Zero Page X

        //ASSERT LDA - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::Absolute);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Absolute

        //ASSERT LDA - Absolute X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::AbsoluteX);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Absolute X

        //ASSERT LDA - Absolute Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::AbsoluteY);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Absolute Y


        //ASSERT LDA - Indirect X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::IndirectX);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(6);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(6);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x20;
        mem[0x20] = 0x41;
        mem[0x21] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(6);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Indirect X

        //ASSERT LDA - Indirect Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDA::IndirectY);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x86;
        mem[0x86] = 0x28;
        mem[0x87] = 0x40;
        mem[0x4028] = 40;
        cpu.execute(5);
        assert(cpu.get_registers().ACU.get() == 40
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x86;
        mem[0x86] = 0x28;
        mem[0x87] = 0x40;
        mem[0x4028] = 0x0;
        cpu.execute(5);
        assert(cpu.get_registers().ACU.get() == 0
               && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x86;
        mem[0x86] = 0x28;
        mem[0x87] = 0x40;
        mem[0x4028] = 128;
        cpu.execute(5);
        assert(cpu.get_registers().ACU.get() == 128
               && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
               && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDA - Indirect Y
        return true;
    }
}
#endif
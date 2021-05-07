#ifndef cpu6502_TEST_LDY
#define cpu6502_TEST_LDY

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool LDY_TEST() noexcept
    {
        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        auto p = PSFlags::BreakCommand;
        (void)p;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;
        //ASSERT LDY - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::Immediate);
        cpu.reset();
        auto PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 40;
        cpu.execute(2);

        all_good &= (cpu.get_registers().IRY.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0;
        cpu.execute(2);

        all_good &= (cpu.get_registers().IRY.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));

        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 128;
        cpu.execute(2);

        all_good &= (cpu.get_registers().IRY.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDY - Immediate

//ASSERT LDY - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::ZeroPage);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);

        all_good &= (cpu.get_registers().IRY.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(3);

        all_good &= (cpu.get_registers().IRY.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(3);

        all_good &= (cpu.get_registers().IRY.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDY - Zero Page


        //ASSERT LDY - Zero Page X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::ZeroPageX);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDY - Zero Page X

        //ASSERT LDY - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::Absolute);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDY - Absolute

        //ASSERT LDY - Absolute X
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDY::AbsoluteX);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRY.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDY - Absolute X

        return all_good;
    }
}
#endif
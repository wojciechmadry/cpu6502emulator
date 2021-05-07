#ifndef cpu6502_TEST_LDX
#define cpu6502_TEST_LDX

#include <cassert>
#include "../../cpu6502/cpu.hpp"

namespace CPU6502_TEST::inner{
    bool LDX_TEST() noexcept
    {

        bool all_good = true;

        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        auto p = PSFlags::BreakCommand;
        (void)p;

        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;
        //ASSERT LDX - Immediate
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDX::Immediate);
        cpu.reset();
        auto PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 40;
        cpu.execute(2);

        all_good &= (cpu.get_registers().IRX.get() == 40
                    && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                    && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0;
        cpu.execute(2);

        all_good &= (cpu.get_registers().IRX.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 128;
        cpu.execute(2);

        all_good &= (cpu.get_registers().IRX.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDX - Immediate

//ASSERT LDX - Zero Page
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDX::ZeroPage);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(3);

        all_good &= (cpu.get_registers().IRX.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(3);

        all_good &= (cpu.get_registers().IRX.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(3);

        all_good &= (cpu.get_registers().IRX.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDX - Zero Page


        //ASSERT LDX - Zero Page Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDX::ZeroPageY);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 40;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 0x0;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0xFF;
        mem[0xFF] = 128;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDX - Zero Page Y

        //ASSERT LDX - Absolute
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDX::Absolute);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDX - Absolute
        
        //ASSERT LDX - Absolute Y
        opcode = static_cast<decltype(opcode)>(cpu6502::opcode::LDX::AbsoluteY);
        cpu.reset();
        PC = cpu.get_registers().PC.get();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 40;
        cpu.execute(4);
        all_good &= (cpu.get_registers().IRX.get() == 40
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 0x0;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 0
                     && cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && !cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        cpu.reset();
        mem[PC] = opcode;
        mem[PC + 1] = 0x41;
        mem[PC + 2] = 0x47;
        mem[0x4741] = 128;
        cpu.execute(4);

        all_good &= (cpu.get_registers().IRX.get() == 128
                     && !cpu.get_registers().PS.get(PSFlags::ZeroFlag)
                     && cpu.get_registers().PS.get(PSFlags::NegativeFlag));
        //END ASSERT LDX - Absolute Y
        
        return all_good;
    }
}
#endif
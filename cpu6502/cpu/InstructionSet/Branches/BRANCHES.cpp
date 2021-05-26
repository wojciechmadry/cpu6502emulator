#include "cpu.hpp"
namespace cpu6502{
    void CPU::branch_if(u32& Cycles, bool If) noexcept
    {
        // 3 cycles
        auto Fetched = static_cast<SByte>(fetch_byte(Cycles));
        // 2 Cycles
        if( If )
        {
            Word PC = cpu_reg.PC.get();
            cpu_reg.PC.set(static_cast<Word>(PC + Fetched));
            --Cycles;

            // 1 Cycles
            if ( (cpu_reg.PC.get() >> 8) != (PC>>8) )
            {
                --Cycles;
                // 0 Cycles
            }
        }

    }
    void CPU::BRANCHES() noexcept
    {
        auto cast = []<typename T>(T reg) -> cpu6502::Byte
        {
            return static_cast<cpu6502::Byte>(reg);
        };

        LookUpTable[cast(cpu6502::opcode::BCC::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, !cpu.cpu_reg.PS.get(PSFlags::CarryFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BCS::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, cpu.cpu_reg.PS.get(PSFlags::CarryFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BEQ::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, cpu.cpu_reg.PS.get(PSFlags::ZeroFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BMI::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, cpu.cpu_reg.PS.get(PSFlags::NegativeFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BNE::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, !cpu.cpu_reg.PS.get(PSFlags::ZeroFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BPL::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, !cpu.cpu_reg.PS.get(PSFlags::NegativeFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BVC::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, !cpu.cpu_reg.PS.get(PSFlags::OverflowFlag));
        };

        LookUpTable[cast(cpu6502::opcode::BVS::Relative)] = [](u32& Cycles, CPU& cpu) -> void
        {
            cpu.branch_if(Cycles, cpu.cpu_reg.PS.get(PSFlags::OverflowFlag));
        };
    }
}
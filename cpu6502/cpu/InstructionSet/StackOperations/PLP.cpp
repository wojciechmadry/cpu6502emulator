#include "cpu.hpp"

namespace cpu6502{

    void CPU::PLPimplied(u32& Cycles) noexcept
    {
        // 3 Cycles;
        Byte ProcessorStatus = pop_byte_from_stack(Cycles);
        // 1 Cycles;
        cpu_reg.PS.put_byte(ProcessorStatus);
        --Cycles;
        // 0 Cycles
    }
    // remove this
    /*
    void CPU::PLP() noexcept
    {
        using op = cpu6502::opcode::PLP;
        LookUpTable[static_cast<Byte>(op::Implied)] = [](u32 &Cycles, CPU &cpu) -> void {
            // 3 Cycles;
            Byte ProcessorStatus = cpu.pop_byte_from_stack(Cycles);
            // 1 Cycles;
            cpu.cpu_reg.PS.put_byte(ProcessorStatus);
            --Cycles;
            // 0 Cycles
        };
    }*/
}
#include "cpu.hpp"

namespace cpu6502{
    void CPU::execute(u32 Cycles) noexcept
    {
        while( Cycles > 0)
        {
            u32 OldCycles = Cycles;

            Byte ins = fetch_byte(Cycles);
            bool FunctionCalled = false;

            for(const auto& Function : InstructionSetArray)
                if (Function(ins, Cycles))
                {
                    FunctionCalled = true;
                    break;
                }


            assert(Cycles < OldCycles);
            assert(FunctionCalled);
        }
    }
}
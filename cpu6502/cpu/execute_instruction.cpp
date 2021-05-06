#include "cpu.hpp"

namespace cpu6502{
    void CPU::execute(u32 Cycles) noexcept
    {
        while( Cycles > 0)
        {
            u32 OldCycles = Cycles;

            Byte ins = fetch_byte(Cycles);
            bool FunctionCalled = false;

            if(LDA(ins, Cycles) ||
               JSR(ins, Cycles) || JMP(ins, Cycles) || RTS(ins, Cycles) )
                FunctionCalled = true;



            assert(Cycles < OldCycles);
            assert(FunctionCalled);
        }
    }
}
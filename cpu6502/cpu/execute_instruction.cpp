#include "cpu.hpp"

namespace cpu6502{
    void CPU::execute(u32 Cycles) noexcept
    {
        while( Cycles > 0)
        {
            u32 OldCycles = Cycles;

            Byte ins = fetch_byte(Cycles);
            LookUpTable[ins](Cycles);

            assert(Cycles < OldCycles);
        }
    }
}
#include "cpu.hpp"


namespace cpu6502{
    CPU::CPU(cpu6502::Memory &memory) noexcept: mem(memory)
    {
        reset();
        LDA();
        LDX();
        JSR();
        JMP();
        RTS();
        LDY();
        STA();
        STX();
        STY();
        CLC();
        CLD();
        CLI();
        CLV();
        SEC();
        SED();
        SEI();
        TAX();
        TAY();
        TXA();
        TYA();
    }

    void CPU::execute(u32 Cycles) noexcept
    {
        while ( Cycles > 0 )
        {
            u32 OldCycles = Cycles;

            Byte ins = fetch_byte(Cycles);
            LookUpTable[ins](Cycles, *this);

            assert(Cycles < OldCycles);
        }
    }
}
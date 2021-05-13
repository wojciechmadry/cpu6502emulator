#include "cpu.hpp"


namespace cpu6502{
    //Look up table to all instruction function
    std::array<CPU::Func* , 256> CPU::LookUpTable;
    bool CPU::LookUpTableInit = false;

    CPU::CPU(cpu6502::Memory &memory) noexcept: mem(memory)
    {
        reset();
        if (!LookUpTableInit)
        {
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
            LookUpTableInit = true;
        }
    }

    void CPU::execute(u32 Cycles) noexcept
    {
        while ( Cycles > 0 )
        {
            u32 OldCycles = Cycles;
            (void) OldCycles; // REMEMBER TO DELETE THIS!!

            Byte ins = fetch_byte(Cycles);
            LookUpTable[ins](Cycles, *this);

            assert(Cycles < OldCycles);
        }
    }
}
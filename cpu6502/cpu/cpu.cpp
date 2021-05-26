#include "cpu.hpp"


namespace cpu6502{
    //Look up table to all instruction function
    std::array<CPU::Func* , 256> CPU::LookUpTable;
    bool CPU::LookUpTableInit = false;

    void CPU::reset() noexcept
    {
        cpu_reg.PC.set(0xFFFA);
        cpu_reg.SP.set(0xFF);
        cpu_reg.PS.put_byte(0x00);
        cpu_reg.ACU.set(0);
        cpu_reg.IRX.set(0);
        cpu_reg.IRY.set(0);
        mem.get().initialise();
    }

    CPU::CPU(cpu6502::Memory &memory) noexcept: mem(memory)
    {
        reset();
        if (!LookUpTableInit)
        {
            _init();
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


    void CPU::_init() noexcept
    {
        BRANCHES();
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
        TSX();
        TXS();
        PHA();
        PHP();
        PLA();
        PLP();
        AND();
        EOR();
        ORA();
        BIT();
    }
}
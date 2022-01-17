#ifndef CPU_6502_processor
#define CPU_6502_processor

#include "memory/memory.hpp"
#include "registers/registers.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool BRANCHES_TEST() noexcept;  // remove this
}

namespace cpu6502
{

    class CPU
    {
        //CPU registers
        cpu6502::Registers cpu_reg;

        //RAM
        std::reference_wrapper<cpu6502::Memory> mem;

        //Processor Status flags
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;


        //Look up table to all instruction function
        //using Func = void(u32&, CPU&);
        //static std::array<Func* , 256> LookUpTable;
        //static bool LookUpTableInit;

        // Read CPU
        [[nodiscard]] Byte fetch_byte(u32& Cycles) noexcept;
        [[nodiscard]] Byte read_byte(u32 Address, u32& Cycles) const noexcept;
        [[nodiscard]] Word fetch_word(u32& Cycles) noexcept;
        [[nodiscard]] Word read_word(u32 Address, u32& Cycles) noexcept;
        [[nodiscard]] Word pop_word_from_stack(u32& Cycles);
        [[nodiscard]] Byte pop_byte_from_stack(u32& Cycles);

        // Write CPU
        void write_word(Word Data, u32 Address, u32& Cycles) noexcept;
        void write_byte(Byte Data, u32 Address, u32& Cycles) noexcept;
        void push_word_to_stack(Word Data, u32& Cycles);
        void push_byte_to_stack(Byte Data, u32& Cycles);



/*      // remove this
        //Initialise Instruction Set in LookUpTable

        // Load/Store Operations
        static void LDA() noexcept; // Load Accumulator
        static void LDX() noexcept; // Load X Register
        static void LDY() noexcept; // Load Y Register
        static void STA() noexcept; // Store Accumulator
        static void STX() noexcept; // Store X Register
        static void STY() noexcept; // Store Y Register

        // Jumps & Calls
        static void JSR() noexcept; // Jump to a subroutine
        static void JMP() noexcept; // Jump to another location
        static void RTS() noexcept; // Return from Subroutine

        // Status Flag Changes
        static void CLC() noexcept; // Clear carry flag
        static void CLD() noexcept; // Clear decimal mode flag
        static void CLI() noexcept; // Clear interrupt disable flag
        static void CLV() noexcept; // Clear overflow flag
        static void SEC() noexcept; // Set carry flag
        static void SED() noexcept; // Set decimal mode flag
        static void SEI() noexcept; // Set interrupt disable flag

        // Register Transfers
        static void TAX() noexcept; // Transfer Accumulator to X
        static void TAY() noexcept; // Transfer Accumulator to Y
        static void TXA() noexcept; // Transfer X to Accumulator
        static void TYA() noexcept; // Transfer Y to Accumulator


        // Stack Operations
        static void TSX() noexcept; // Transfer stack pointer to X
        static void TXS() noexcept; // Transfer X to stack pointer
        static void PHA() noexcept; // Push accumulator on stack
        static void PHP() noexcept; // Push processor status on stack
        static void PLA() noexcept; // Pull accumulator from stack
        static void PLP() noexcept; // Pull processor status from stack

        // LOGICAL
        static void AND() noexcept; // Logical AND
        static void EOR() noexcept; // Exclusive OR
        static void ORA() noexcept; // Logical Inclusive OR
        static void BIT() noexcept; // Bit Test
/*
        // BRANCHES
        /*  BCC - Branch if carry flag clear
         *  BCS - Branch if carry flag set
         *  BEQ - Branch if zero flag set
         *  BMI - Branch if negative flag set
         *  BNE - Branch if zero flag clear
         *  BPL - Branch if negative flag clear
         *  BVC - Branch if overflow flag clear
         *  BVS - Branch if overflow flag set
         */
       /* static void BRANCHES() noexcept;
        void branch_if(u32& Cycles, bool If) noexcept;
        // END - Instruction Set

        // ARITHMETIC
        static void ADC() noexcept; // Add with Carry
        static void SBC() noexcept; // Subtract with Carry
        static void CMP() noexcept; // Compare accumulator
        static void CPX() noexcept; // Compare X register
        static void CPY() noexcept; // Compare Y register

        static void _init() noexcept;*/

        //FIREND'S FUNCTION
        friend bool CPU6502_TEST::inner::BRANCHES_TEST() noexcept; // remove this

        // Instruction set functions

        // --- ARITHMETIC ---
        //      -- ADC --
    void ADCimmediate(u32& Cycles) noexcept;
    void ADCzeropage(u32& Cycles) noexcept;
    void ADCzeropagex(u32& Cycles) noexcept;
    void ADCabsolute(u32& Cycles) noexcept;
    void ADCabsolutex(u32& Cycles) noexcept;
    void ADCabsolutey(u32& Cycles) noexcept;
    void ADCindirectx(u32& Cycles) noexcept;
    void ADCindirecty(u32& Cycles) noexcept;
        //      -- CMP --
    void CMPimmediate(u32& Cycles) noexcept;
    void CMPzeropage(u32& Cycles) noexcept;
    void CMPzeropagex(u32& Cycles) noexcept;
    void CMPabsolute(u32& Cycles) noexcept;
    void CMPabsolutex(u32& Cycles) noexcept;
    void CMPabsolutey(u32& Cycles) noexcept;
    void CMPindirectx(u32& Cycles) noexcept;
    void CMPindirecty(u32& Cycles) noexcept;
        //      -- CPX  --
    void CPXimmediate(u32& Cycles) noexcept;
    void CPXzeropage(u32& Cycles) noexcept;
    void CPXabsolute(u32& Cycles) noexcept;
        //      -- CPY  --
    void CPYimmediate(u32& Cycles) noexcept;
    void CPYzeropage(u32& Cycles) noexcept;
    void CPYabsolute(u32& Cycles) noexcept;
        //      -- SBC --
    void SBCimmediate(u32& Cycles) noexcept;
    void SBCzeropage(u32& Cycles) noexcept;
    void SBCzeropagex(u32& Cycles) noexcept;
    void SBCabsolute(u32& Cycles) noexcept;
    void SBCabsolutex(u32& Cycles) noexcept;
    void SBCabsolutey(u32& Cycles) noexcept;
    void SBCindirectx(u32& Cycles) noexcept;
    void SBCindirecty(u32& Cycles) noexcept;

        // --- BRANCHES ---
    void branch_if(u32& Cycles, bool If) noexcept;
    void BRANCHbcc(u32& Cycles) noexcept;
    void BRANCHbcs(u32& Cycles) noexcept;
    void BRANCHbeq(u32& Cycles) noexcept;
    void BRANCHbmi(u32& Cycles) noexcept;
    void BRANCHbne(u32& Cycles) noexcept;
    void BRANCHbpl(u32& Cycles) noexcept;
    void BRANCHbvc(u32& Cycles) noexcept;
    void BRANCHbvs(u32& Cycles) noexcept;

        // --- Jumps Calls --- // 18.01
        //      -- JMP --
        //      -- JSR --
        //      -- RTS --

        // --- Load Store Operations --- // 19.01
        //      -- LDA --
        //      -- LDX --
        //      -- LDY --
        //      -- STA --
        //      -- STX --
        //      -- STY --

        // --- Logical ---   // 20.01
        //      -- AND --
        //      -- BIT --
        //      -- EOR --
        //      -- ORA --

        // --- Register Transfer ---  // 21.01
        //      -- TAX --
        //      -- TAY --
        //      -- TXA --
        //      -- TYA --

        // --- Stack operations ---  // 24.01
        //      -- PHA --
        //      -- PHP --
        //      -- PLA --
        //      -- PLP --
        //      -- TSX --
        //      -- TXS --

        // --- Status Flag Changes ---  // 25.01
        //      -- CLC --
        //      -- CLD --
        //      -- CLI --
        //      -- CLV --
        //      -- SEC --
        //      -- SED --
        //      -- SEI --


    public:
        CPU() = delete;
        CPU(const CPU&) = delete;
        CPU(CPU&&) = delete;
        explicit CPU(cpu6502::Memory& memory) noexcept;

        ~CPU() = default;

        [[nodiscard]] const cpu6502::Registers& get_registers() const noexcept
        {
            return cpu_reg;
        }

        void reset() noexcept;

        void execute(u32 Cycles);
    };


}


#endif
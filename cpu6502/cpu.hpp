#ifndef CPU_6502_processor
#define CPU_6502_processor

#include "registers/registers.hpp"
#include "memory/memory.hpp"
#include "cpu/InstructionSet/opcode.hpp"


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
        using Func = void(u32&, CPU&);
        static std::array<Func* , 256> LookUpTable;
        static bool LookUpTableInit;

        // Read CPU
        [[nodiscard]] Byte fetch_byte(u32& Cycles) noexcept;
        [[nodiscard]] Byte read_byte(u32 Address, u32& Cycles) const noexcept;
        [[nodiscard]] Word fetch_word(u32& Cycles) noexcept;
        [[nodiscard]] Word read_word(u32 Address, u32& Cycles) noexcept;
        [[nodiscard]] Word pop_word_from_stack(u32& Cycles) noexcept;
        [[nodiscard]] Byte pop_byte_from_stack(u32& Cycles) noexcept;

        // Write CPU
        void write_word(Word Data, u32 Address, u32& Cycles) noexcept;
        void write_byte(Byte Data, u32 Address, u32& Cycles) noexcept;
        void push_word_to_stack(Word Data, u32& Cycles) noexcept;
        void push_byte_to_stack(Byte Data, u32& Cycles) noexcept;


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
        // END - Instruction Set

        static void _init() noexcept;
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

        void execute(u32 Cycles) noexcept;
    };


}


#endif
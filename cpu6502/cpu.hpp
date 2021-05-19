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
        void LDA() noexcept; // Load Accumulator
        void LDX() noexcept; // Load X Register
        void LDY() noexcept; // Load Y Register
        void STA() noexcept; // Store Accumulator
        void STX() noexcept; // Store X Register
        void STY() noexcept; // Store Y Register

        // Jumps & Calls
        void JSR() noexcept; // Jump to a subroutine
        void JMP() noexcept; // Jump to another location
        void RTS() noexcept; // Return from Subroutine

        // Status Flag Changes
        void CLC() noexcept; // Clear carry flag
        void CLD() noexcept; // Clear decimal mode flag
        void CLI() noexcept; // Clear interrupt disable flag
        void CLV() noexcept; // Clear overflow flag
        void SEC() noexcept; // Set carry flag
        void SED() noexcept; // Set decimal mode flag
        void SEI() noexcept; // Set interrupt disable flag

        // Register Transfers
        void TAX() noexcept; // Transfer Accumulator to X
        void TAY() noexcept; // Trnasfer Accumulator to Y
        void TXA() noexcept; // Trnasfer X to Accumulator
        void TYA() noexcept; // Trnasfer Y to Accumulator


        // Stack Operations
        void TSX() noexcept;
        void TXS() noexcept;
        void PHA() noexcept;
        void PHP() noexcept;
        void PLA() noexcept;
        void PLP() noexcept;

        // END - Instruction Set
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
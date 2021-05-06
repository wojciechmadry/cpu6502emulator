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
        // ON STACK
        std::array<std::function<void(u32&)>, 256> LookUpTable;
        // ON HEAP
        //std::vector<std::function<void(u32&)>> LookUpTable {256} ;

        // Read CPU
        [[nodiscard]] Byte fetch_byte(u32& Cycles) noexcept;
        [[nodiscard]] Byte read_byte(u32 Address, u32& Cycles) const noexcept;
        [[nodiscard]] Word fetch_word(u32& Cycles) noexcept;
        [[nodiscard]] Word read_word(u32 Address, u32& Cycles) noexcept;
        [[nodiscard]] Word fetch_word_from_stack(u32& Cycles) noexcept;
        [[nodiscard]] Byte fetch_byte_from_stack(u32& Cycles) noexcept;

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

        // Jumps & Calls
        void JSR() noexcept; // Jump to a subroutine
        void JMP() noexcept; // Jump to another location
        void RTS() noexcept; // Return from Subroutine

        // END - Instruction Set
    public:
        CPU() = delete;
        CPU(const CPU&) = delete;
        CPU(CPU&&) = delete;
        explicit CPU(cpu6502::Memory& memory) noexcept : mem(memory)
        {
            reset();
            LDA();
            LDX();
            JSR();
            JMP();
            RTS();
            LDY();
        }

        ~CPU() = default;

        [[nodiscard]] const cpu6502::Registers& get_registers() const noexcept
        {
            return cpu_reg;
        }

        void reset() noexcept
        {
            cpu_reg.PC.set(0xFFFC);
            cpu_reg.SP.set(0x00);
            cpu_reg.PS.put_byte(0x00);
            cpu_reg.ACU.set(0);
            cpu_reg.IRX.set(0);
            cpu_reg.IRY.set(0);
            mem.get().initialise();
        }

        void execute(u32 Cycles) noexcept;
    };
}

#endif
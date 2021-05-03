#ifndef CPU_6502_processor
#define CPU_6502_processor

#include "registers.hpp"
#include "memory.hpp"
#include "InstructionSet/opcode.hpp"

#include <iostream>
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

        [[nodiscard]] Byte fetch_byte(u32& Cycles) noexcept
        {
            Byte Data = mem.get()[cpu_reg.PC.get()];
            cpu_reg.PC.increment();
            --Cycles;
            return Data;
        }

        [[nodiscard]] Byte read_byte(const u32 Address, u32& Cycles) const noexcept
        {
            --Cycles;
            return mem.get()[Address];
        }

        [[nodiscard]] Word fetch_word(u32& Cycles) noexcept {
            //little endian
            Word Data = mem.get()[cpu_reg.PC.get()];
            cpu_reg.PC.increment();
            Data = static_cast<Word>(Data | (mem.get()[cpu_reg.PC.get()] << 8));
            cpu_reg.PC.increment();
            Cycles -= 2;
            return Data;
        }

        [[nodiscard]] Word read_word(const u32 Address, u32& Cycles) noexcept
        {
            //little endian
            Cycles -= 2;
            return mem.get().read_word(Address);
        }
        void write_word(Word Data, u32 Address, u32& Cycles) noexcept
        {
            mem.get().write_word(Data, Address);
            Cycles -= 2;
        }

        // Load/Store Operations
        [[nodiscard]] bool LDA(Byte Opcode, u32& Cycles) noexcept; // LOAD ACCUMULATOR

        // Jumps & Calls
        [[nodiscard]] bool JSR(Byte Opcode, u32& Cycles) noexcept; // Jump to a subroutine
        [[nodiscard]] bool JMP(Byte Opcode, u32& Cycles) noexcept; // Jump to another location

    public:
        CPU() = delete;
        explicit CPU(cpu6502::Memory& memory) noexcept : mem(memory)
        {}
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

        void execute(u32 Cycles) noexcept
        {
            while( Cycles > 0)
            {
                u32 OldCycles = Cycles;

                Byte ins = fetch_byte(Cycles);
                if (LDA(ins, Cycles))
                    continue;
                if (JSR(ins, Cycles))
                    continue;

                assert(Cycles < OldCycles);
            }
        }
    };
}

#endif
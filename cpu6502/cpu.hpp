#ifndef CPU_6502_processor
#define CPU_6502_processor

#include "required.hpp"
#include "registers.hpp"
#include "memory.hpp"

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
    public:
        CPU() = delete;
        explicit CPU(cpu6502::Memory& memory) noexcept : mem(memory)
        {}
        ~CPU() = default;

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
                Byte ins = fetch_byte(Cycles);
                (void) ins;
            }
        }
    };
}

#endif
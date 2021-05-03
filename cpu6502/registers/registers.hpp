#ifndef CPU_6502_registers
#define CPU_6502_registers

#include "accumulator.hpp"
#include "indexregisterx.hpp"
#include "indexregistery.hpp"
#include "processorstatus.hpp"
#include "programcounter.hpp"
#include "stackpointer.hpp"

namespace cpu6502{
    struct Registers
    {
        Registers() = default;
        ~Registers() = default;
        cpu6502::registers::ProgramCounter PC; // Program Counter
        cpu6502::registers::StackPointer SP; //Stack Pointer
        cpu6502::registers::ProcessorStatus PS; // Processor Status
        cpu6502::registers::Accumulator ACU; // Accumulator
        cpu6502::registers::IndexRegisterY IRY; // Index Register Y
        cpu6502::registers::IndexRegisterX IRX; // Index Register X
    };
}
#endif
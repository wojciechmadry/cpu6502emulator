#ifndef CPU_6502_registers
#define CPU_6502_registers

#include "registers/accumulator.hpp"
#include "registers/indexregisterx.hpp"
#include "registers/indexregistery.hpp"
#include "registers/processorstatus.hpp"
#include "registers/programcounter.hpp"
#include "registers/stackpointer.hpp"

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
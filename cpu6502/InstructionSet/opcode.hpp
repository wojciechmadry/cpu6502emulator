#ifndef CPU_6502_processor_opcode
#define CPU_6502_processor_opcode

namespace cpu6502::opcode{
    //Load Accumulator opcode
    enum class LDA : Byte {
        Immediate = 0xA9, // 2 cycles - Implemented
        ZeroPage = 0xA5, // 3 cycles - Implemented
        ZeroPageX = 0xB5, // 4 cycles - Implemented
        Absolute = 0xAD, // 4 cycles - Implemented
        AbsoluteX = 0xBD, // 4 cycles (+1 if page crossed) - Implemented
        AbsoluteY = 0xB9, // 4 cycles (+1 if page crossed) - Implemented
        IndirectX = 0xA1, // 6 cycles - Implemented
        IndirectY = 0xB1 // 5 cycles (+1 if page crossed) - Implemented
    };

    //Jump to Subroutine opcode
    enum class JSR : Byte{
        Absolute = 0x20 // 6 cycles - Implemented
    };

    //Jump to to another location opcode
    enum class JMP : Byte{
        Absolute = 0x4C, // 3 cycles - Implemented
        Indirect = 0x6C // 5 cycles - Implemented
    };

    //Return from Subroutine
    enum class RTS : Byte{
        Implied = 0x60, // 6 cycles
    };
}
#endif
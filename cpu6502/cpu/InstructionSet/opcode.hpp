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

    // Load X register opcode
    enum class LDX : Byte
    {
        Immediate = 0xA2, // 2 cycles - Implemented
        ZeroPage = 0xA6, // 3 cycles - Implemented
        ZeroPageY = 0xB6, // 4 cycles - Implemented
        Absolute = 0xAE, // 4 cycles - Implemented
        AbsoluteY = 0xBE // 4 cycles (+1 if page crossed) - Implemented
    };


    //Load Y register opcode
    enum class LDY : Byte
    {
        Immediate = 0xA0, // 2 cycles - Implemented
        ZeroPage = 0xA4, // 3 cycles - Implemented
        ZeroPageX = 0xB4, // 4 cycles - Implemented
        Absolute = 0xAC, // 4 cycles - Implemented
        AbsoluteX = 0xBC // 4 cycles (+1 if page crossed) - Implemented
    };

    //Store Accumulator opcode
    enum class STA : Byte
    {
        ZeroPage = 0x85, // 3 cycles - Implemented
        ZeroPageX = 0x95, // 4 cycles - Implemented
        Absolute = 0x8D, // 4 cycles - Implemented
        AbsoluteX = 0x9D, // 5 cycles - Implemented
        AbsoluteY = 0x99, // 5 cycles - Implemented
        IndircetX = 0x81, // 6 cycles - Implemented
        IndircetY = 0x91 // 6 cycles - Implemented
    };

    // Store X Register opcode
    enum class STX : Byte
    {
        ZeroPage = 0x86, // 3 cycles
        ZeroPageY = 0x96, // 4 cycles
        Absolute = 0x8E // 4 cycles
    };

    // Store Y Register opcode
    enum class STY : Byte
    {
        ZeroPage = 0x84, // 3 cycles
        ZeroPageX = 0x94, // 4 cycles
        Absolute = 0x8C // 4 cycles
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
        Implied = 0x60 // 6 cycles - Implemented im not sure if its working good.
    };
}
#endif
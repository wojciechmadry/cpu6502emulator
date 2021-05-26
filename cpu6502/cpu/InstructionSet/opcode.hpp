#ifndef CPU_6502_processor_opcode
#define CPU_6502_processor_opcode

namespace cpu6502::opcode{

    // *** Load/Store Operations ***

    //Load Accumulator opcode
    enum class LDA : Byte {
        Immediate = 0xA9, // 2 cycles - Implemented
        ZeroPage = 0xA5, // 3 cycles - Implemented
        ZeroPageX = 0xB5, // 4 cycles - Implemented
        Absolute = 0xAD, // 4 cycles - Implemented
        AbsoluteX = 0xBD, // 4 cycles (+1 if page crossed) - Implemented - Page Cross
        AbsoluteY = 0xB9, // 4 cycles (+1 if page crossed) - Implemented - Page Cross
        IndirectX = 0xA1, // 6 cycles - Implemented
        IndirectY = 0xB1 // 5 cycles (+1 if page crossed) - Implemented - Page Cross
    };

    // Load X register opcode
    enum class LDX : Byte
    {
        Immediate = 0xA2, // 2 cycles - Implemented
        ZeroPage = 0xA6, // 3 cycles - Implemented
        ZeroPageY = 0xB6, // 4 cycles - Implemented
        Absolute = 0xAE, // 4 cycles - Implemented
        AbsoluteY = 0xBE // 4 cycles (+1 if page crossed) - Implemented - Page Cross
    };


    //Load Y register opcode
    enum class LDY : Byte
    {
        Immediate = 0xA0, // 2 cycles - Implemented
        ZeroPage = 0xA4, // 3 cycles - Implemented
        ZeroPageX = 0xB4, // 4 cycles - Implemented
        Absolute = 0xAC, // 4 cycles - Implemented
        AbsoluteX = 0xBC // 4 cycles (+1 if page crossed) - Implemented - Page cross
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
        ZeroPage = 0x86, // 3 cycles - Implemented
        ZeroPageY = 0x96, // 4 cycles - Implemented
        Absolute = 0x8E // 4 cycles - Implemented
    };

    // Store Y Register opcode
    enum class STY : Byte
    {
        ZeroPage = 0x84, // 3 cycles - Implemented
        ZeroPageX = 0x94, // 4 cycles- Implemented
        Absolute = 0x8C // 4 cycles- Implemented
    };

    // *** Load/Store Operations ***

    // *** Jump & Calls ***

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

    // *** Jump & Calls ***

    // *** Status Flag Changes ***

    //Clear carry flag
    enum class CLC : Byte{
        Implied = 0x18 // 2 cycles - implemented
    };

    //Clear decimal mode flag
    enum class CLD : Byte{
        Implied = 0xD8 // 2 cycles - implemented
    };

    //Clear interrupt disable flag
    enum class CLI : Byte{
        Implied = 0x58 // 2 cycles - implemented
    };

    //Clear overflow flag
    enum class CLV : Byte{
        Implied = 0xB8 // 2 cycles - implemented
    };

    //Set carry flag
    enum class SEC : Byte{
        Implied = 0x38 // 2 cycles - implemented
    };

    //Set decimal mode flag
    enum class SED : Byte{
        Implied = 0xF8 // 2 cycles - implemented
    };

    //Set interrupt disable flag
    enum class SEI : Byte{
        Implied = 0x78 // 2 cycles - implemented
    };

    // *** Status Flag Changes ***

    // *** Register Transfers ***

    // Transfer Accumulator to X
    enum class TAX : Byte
    {
        Implied = 0xAA // 2 cycles - Implemented
    };

    // Transfer Accumulator to Y
    enum class TAY : Byte
    {
        Implied = 0xA8 // 2 cycles - Implemented
    };

    // Transfer X to Accumulator
    enum class TXA : Byte
    {
        Implied = 0x8A // 2 cycles - Implemented
    };

    // Transfer Y to Accumulator
    enum class TYA : Byte
    {
        Implied = 0x98 // 2 cycles - Implemented
    };

    // *** Register Transfers ***

    // *** Stack Operations ***

    // Transfer stack pointer to X

    enum class TSX : Byte
    {
        Implied = 0xBA // 2 cycles - Implemented
    };

    // Transfer X to stack pointer

    enum class TXS : Byte
    {
        Implied = 0x9A // 2 cycles - Implemented
    };

    // Push accumulator on stack

    enum class PHA : Byte
    {
        Implied = 0x48 // 3 cycles - Implemented
    };

    // Push processor status on stack

    enum class PHP : Byte
    {
        Implied = 0x08 // 3 cycles - Implemented
    };

    // Pull accumulator from stack

    enum class PLA : Byte
    {
        Implied = 0x68 // 4 cycles - Implemented
    };

    // Pull processor status from stack

    enum class PLP : Byte
    {
        Implied = 0x28 // 4 cycles - Implemented
    };

    // *** Stack Operations ***


    // *** Logical ***

    enum class AND : Byte
    {
        Immediate = 0x29, // 2 Cycles - Implemented
        ZeroPage = 0x25,  // 3 Cycles - Implemented
        ZeroPageX = 0x35, // 4 Cycles - Implemented
        Absolute = 0x2D,  // 4 Cycles - Implemented
        AbsoluteX = 0x3D, // 4 (+1 if page crossed) Cycles - Implemented - Page cross
        AbsoluteY = 0x39, // 4 (+1 if page crossed)  Cycles - Implemented - Page cross
        IndirectX = 0x21, // 6 Cycles - Implemented
        IndirectY = 0x31  // 5 (+1 if page crossed)  Cycles - Implemented - Page cross
    };

    enum class EOR : Byte
    {
        Immediate = 0x49, // 2 Cycles - Implemented
        ZeroPage = 0x45,  // 3 Cycles - Implemented
        ZeroPageX = 0x55, // 4 Cycles - Implemented
        Absolute = 0x4D,  // 4 Cycles - Implemented
        AbsoluteX = 0x5D, // 4 (+1 if page crossed) Cycles - Implemented - Page cross
        AbsoluteY = 0x59, // 4 (+1 if page crossed) Cycles - Implemented - Page cross
        IndirectX = 0x41, // 6 Cycles - Implemented
        IndirectY = 0x51  // 5 (+1 if page crossed)  Cycles - Implemented - Page cross
    };

    enum class ORA : Byte
    {
        Immediate = 0x09, // 2 Cycles - Implemented
        ZeroPage = 0x05,  // 3 Cycles - Implemented
        ZeroPageX = 0x15, // 4 Cycles - Implemented
        Absolute = 0x0D,  // 4 Cycles - Implemented
        AbsoluteX = 0x1D, // 4 (+1 if page crossed) Cycles - Implemented - Page cross
        AbsoluteY = 0x19, // 4 (+1 if page crossed)  Cycles - Implemented - Page cross
        IndirectX = 0x01, // 6 Cycles - Implemented
        IndirectY = 0x11  // 5 (+1 if page crossed)  Cycles - Implemented - Page cross
    };

    enum class BIT : Byte
    {
        ZeroPage = 0x24,  // 3 Cycles - Implemented
        Absolute = 0x2C,  // 4 Cycles - Implemented
    };

    // *** Logical ***

    // *** Branches ***

    enum class BCC : Byte
    {
        Relative = 0x90 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BCS : Byte
    {
        Relative = 0xB0 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BEQ : Byte
    {
        Relative = 0xF0 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BMI : Byte
    {
        Relative = 0x30 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BNE : Byte
    {
        Relative = 0xD0 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BPL : Byte
    {
        Relative = 0x10 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BVC : Byte
    {
        Relative = 0x50 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    enum class BVS : Byte
    {
        Relative = 0x70 // 2 ( +1 if branch success, +2 if to a new page) - Implemented
    };

    // *** Branches ***
}
#endif
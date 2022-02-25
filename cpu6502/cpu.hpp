#ifndef CPU_6502_processor
#define CPU_6502_processor

#include "memory/memory.hpp"
#include "registers/registers.hpp"
#include "cpu/InstructionSet/opcode.hpp"
#include "required.hpp"

namespace CPU6502_TEST::inner{
    bool BRANCHES_TEST();  // remove this
}

namespace cpu6502
{
    class CPU
    {
        //CPU registers
        cpu6502::Registers cpu_reg;

        //RAM
        std::reference_wrapper<cpu6502::Memory> mem;

        // Read CPU
        [[nodiscard]] Byte fetch_byte(u32& Cycles) noexcept;
        [[nodiscard]] Byte read_byte(u32 Address, u32& Cycles) const noexcept;
        [[nodiscard]] Word fetch_word(u32& Cycles) noexcept;
        [[nodiscard]] Word read_word(u32 Address, u32& Cycles) noexcept;
        [[nodiscard]] Word pop_word_from_stack(u32& Cycles);
        [[nodiscard]] Byte pop_byte_from_stack(u32& Cycles);

        // Write CPU
        void write_word(Word Data, u32 Address, u32& Cycles) noexcept;
        void write_byte(Byte Data, u32 Address, u32& Cycles) noexcept;
        void push_word_to_stack(Word Data, u32& Cycles);
        void push_byte_to_stack(Byte Data, u32& Cycles);

        // Operation
        // Add value to  Acumulator
        void ADC(const Byte value) noexcept;

        // Fetch data from memory
        cpu6502::Byte fetch_immediate(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_absolute(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_absolutex(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_absolutey(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_indirectx(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_indirecty(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_zeropage(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_zeropagex(cpu6502::u32& Cycles) noexcept;
        cpu6502::Byte fetch_zeropagey(cpu6502::u32& Cycles) noexcept;

        template<AddressingMode mode>
        cpu6502::Byte fetch(cpu6502::u32& Cycles) noexcept
        {
            if constexpr (mode == AddressingMode::Immediate)
            {
                return fetch_immediate(Cycles);
            }
            else if constexpr (mode == AddressingMode::Absolute)
            {
                return fetch_absolute(Cycles);
            }
            else if constexpr (mode == AddressingMode::AbsoluteX)
            {
                return fetch_absolutex(Cycles);
            }
            else if constexpr (mode == AddressingMode::AbsoluteY)
            {
                return fetch_absolutey(Cycles);
            }
            else if constexpr (mode == AddressingMode::IndirectX)
            {
                return fetch_indirectx(Cycles);
            }
            else if constexpr (mode == AddressingMode::IndirectY)
            {
                return fetch_indirecty(Cycles);
            }
            else if constexpr (mode == AddressingMode::ZeroPage)
            {
                return fetch_zeropage(Cycles);
            }
            else if constexpr (mode == AddressingMode::ZeroPageX)
            {
                return fetch_zeropagex(Cycles);
            }
            else if constexpr (mode == AddressingMode::ZeroPageY)
            {
                return fetch_zeropagey(Cycles);
            }
            return static_cast<cpu6502::Byte>(0xFF);
        }

        // BRANCHES
        /*  BCC - Branch if carry flag clear
         *  BCS - Branch if carry flag set
         *  BEQ - Branch if zero flag set
         *  BMI - Branch if negative flag set
         *  BNE - Branch if zero flag clear
         *  BPL - Branch if negative flag clear
         *  BVC - Branch if overflow flag clear
         *  BVS - Branch if overflow flag set
         */


        //FIREND'S FUNCTION
        friend bool CPU6502_TEST::inner::BRANCHES_TEST(); // remove this

        // Instruction set functions

        // --- ARITHMETIC ---
        //      -- ADC --
        void ADCimmediate(u32& Cycles) noexcept;
        void ADCzeropage(u32& Cycles) noexcept;
        void ADCzeropagex(u32& Cycles) noexcept;
        void ADCabsolute(u32& Cycles) noexcept;
        void ADCabsolutex(u32& Cycles) noexcept;
        void ADCabsolutey(u32& Cycles) noexcept;
        void ADCindirectx(u32& Cycles) noexcept;
        void ADCindirecty(u32& Cycles) noexcept;
        //      -- CMP --
        void CMPimmediate(u32& Cycles) noexcept;
        void CMPzeropage(u32& Cycles) noexcept;
        void CMPzeropagex(u32& Cycles) noexcept;
        void CMPabsolute(u32& Cycles) noexcept;
        void CMPabsolutex(u32& Cycles) noexcept;
        void CMPabsolutey(u32& Cycles) noexcept;
        void CMPindirectx(u32& Cycles) noexcept;
        void CMPindirecty(u32& Cycles) noexcept;
        //      -- CPX  --
        void CPXimmediate(u32& Cycles) noexcept;
        void CPXzeropage(u32& Cycles) noexcept;
        void CPXabsolute(u32& Cycles) noexcept;
        //      -- CPY  --
        void CPYimmediate(u32& Cycles) noexcept;
        void CPYzeropage(u32& Cycles) noexcept;
        void CPYabsolute(u32& Cycles) noexcept;
        //      -- SBC --
        void SBCimmediate(u32& Cycles) noexcept;
        void SBCzeropage(u32& Cycles) noexcept;
        void SBCzeropagex(u32& Cycles) noexcept;
        void SBCabsolute(u32& Cycles) noexcept;
        void SBCabsolutex(u32& Cycles) noexcept;
        void SBCabsolutey(u32& Cycles) noexcept;
        void SBCindirectx(u32& Cycles) noexcept;
        void SBCindirecty(u32& Cycles) noexcept;

        // --- BRANCHES ---
        void branch_if(u32& Cycles, bool If) noexcept;
        void BRANCHbcc(u32& Cycles) noexcept;
        void BRANCHbcs(u32& Cycles) noexcept;
        void BRANCHbeq(u32& Cycles) noexcept;
        void BRANCHbmi(u32& Cycles) noexcept;
        void BRANCHbne(u32& Cycles) noexcept;
        void BRANCHbpl(u32& Cycles) noexcept;
        void BRANCHbvc(u32& Cycles) noexcept;
        void BRANCHbvs(u32& Cycles) noexcept;

        // --- Jumps Calls --- 
        //      -- JMP --
        void JMPabsolute(u32& Cycles) noexcept;
        void JMPindirect(u32& Cycles) noexcept;
        //      -- JSR --
        void JSRabsolute(u32& Cycles) noexcept;
        //      -- RTS --
        void RTSimplied(u32& Cycles) noexcept;

        // --- Load Store Operations --- 
        //      -- LDA --
        void LDAimmediate(u32& Cycles) noexcept;
        void LDAzeropage(u32& Cycles) noexcept;
        void LDAzeropagex(u32& Cycles) noexcept;
        void LDAabsolute(u32& Cycles) noexcept;
        void LDAabsolutex(u32& Cycles) noexcept;
        void LDAabsolutey(u32& Cycles) noexcept;
        void LDAindirectx(u32& Cycles) noexcept;
        void LDAindirecty(u32& Cycles) noexcept;

        //      -- LDX --
        void LDXimmediate(u32& Cycles) noexcept;
        void LDXzeropage(u32& Cycles) noexcept;
        void LDXzeropagey(u32& Cycles) noexcept;
        void LDXabsolute(u32& Cycles) noexcept;
        void LDXabsolutey(u32& Cycles) noexcept;

        //      -- LDY --
        void LDYimmediate(u32& Cycles) noexcept;
        void LDYzeropage(u32& Cycles) noexcept;
        void LDYzeropagex(u32& Cycles) noexcept;
        void LDYabsolute(u32& Cycles) noexcept;
        void LDYabsolutex(u32& Cycles) noexcept;

        //      -- STA --
        void STAzeropage(u32& Cycles) noexcept;
        void STAzeropagex(u32& Cycles) noexcept;
        void STAabsolute(u32& Cycles) noexcept;
        void STAabsolutex(u32& Cycles) noexcept;
        void STAabsolutey(u32& Cycles) noexcept;
        void STAindirectx(u32& Cycles) noexcept;
        void STAindirecty(u32& Cycles) noexcept;

        //      -- STX --
        void STXzeropage(u32& Cycles) noexcept;
        void STXzeropagey(u32& Cycles) noexcept;
        void STXabsolute(u32& Cycles) noexcept;

        //      -- STY --

        void STYzeropage(u32& Cycles) noexcept;
        void STYzeropagex(u32& Cycles) noexcept;
        void STYabsolute(u32& Cycles) noexcept;

        // --- Logical ---
        //      -- AND --
        void ANDimmediate(u32& Cycles) noexcept;
        void ANDzeropage(u32& Cycles) noexcept;
        void ANDzeropagex(u32& Cycles) noexcept;
        void ANDabsolute(u32& Cycles) noexcept;
        void ANDabsolutex(u32& Cycles) noexcept;
        void ANDabsolutey(u32& Cycles) noexcept;
        void ANDindirectx(u32& Cycles) noexcept;
        void ANDindirecty(u32& Cycles) noexcept;

        //      -- BIT --
        void BITzeropage(u32& Cycles) noexcept;
        void BITabsolute(u32& Cycles) noexcept;
 
        //      -- EOR --
        void EORimmediate(u32& Cycles) noexcept;
        void EORzeropage(u32& Cycles) noexcept;
        void EORzeropagex(u32& Cycles) noexcept;
        void EORabsolute(u32& Cycles) noexcept;
        void EORabsolutex(u32& Cycles) noexcept;
        void EORabsolutey(u32& Cycles) noexcept;
        void EORindirectx(u32& Cycles) noexcept;
        void EORindirecty(u32& Cycles) noexcept;
 
        //      -- ORA --
        void ORAimmediate(u32& Cycles) noexcept;
        void ORAzeropage(u32& Cycles) noexcept;
        void ORAzeropagex(u32& Cycles) noexcept; 
        void ORAabsolute(u32& Cycles) noexcept;
        void ORAabsolutex(u32& Cycles) noexcept;    
        void ORAabsolutey(u32& Cycles) noexcept;      
        void ORAindirectx(u32& Cycles) noexcept; 
        void ORAindirecty(u32& Cycles) noexcept;

        // --- Increments & Decrements ---

        //      -- DEC --
        void DECzeropage(u32& Cycles) noexcept;
        void DECzeropagex(u32& Cycles) noexcept;
        void DECabsolute(u32& Cycles) noexcept;
        void DECabsolutex(u32& Cycles) noexcept;

        //      -- DEX --
        void DEXimplied(u32& Cycles) noexcept;

        //      -- DEY --
        void DEYimplied(u32& Cycles) noexcept;

        //      -- INC --
        void INCzeropage(u32& Cycles) noexcept;
        void INCzeropagex(u32& Cycles) noexcept;
        void INCabsolute(u32& Cycles) noexcept;
        void INCabsolutex(u32& Cycles) noexcept;
    
        //      -- INX --
        void INXimplied(u32& Cycles) noexcept;
       
        //      -- INY --
        void INYimplied(u32& Cycles) noexcept;

        // --- Shifts ---

        //      -- ROR --
        void RORaccumulator(u32& Cycles) noexcept;
        void RORzeropage(u32& Cycles) noexcept;
        void RORzeropagex(u32& Cycles) noexcept;
        void RORabsolute(u32& Cycles) noexcept;
        void RORabsolutex(u32& Cycles) noexcept;

        //      -- ROL --
        void ROLaccumulator(u32& Cycles) noexcept;
        void ROLzeropage(u32& Cycles) noexcept;
        void ROLzeropagex(u32& Cycles) noexcept;
        void ROLabsolute(u32& Cycles) noexcept;
        void ROLabsolutex(u32& Cycles) noexcept;

        //      -- LSR --
        void LSRaccumulator(u32& Cycles) noexcept;
        void LSRzeropage(u32& Cycles) noexcept;
        void LSRzeropagex(u32& Cycles) noexcept;
        void LSRabsolute(u32& Cycles) noexcept;
        void LSRabsolutex(u32& Cycles) noexcept;

        //      -- ASL --
        void ASLaccumulator(u32& Cycles) noexcept;
        void ASLzeropage(u32& Cycles) noexcept;
        void ASLzeropagex(u32& Cycles) noexcept;
        void ASLabsolute(u32& Cycles) noexcept;
        void ASLabsolutex(u32& Cycles) noexcept;

        // --- Register Transfer --- 
        //      -- TAX --
        void TAXimplied(u32& Cycles) noexcept;
        
        //      -- TAY --
        void TAYimplied(u32& Cycles) noexcept;

        //      -- TXA --
        void TXAimplied(u32& Cycles) noexcept;

        //      -- TYA --
        void TYAimplied(u32& Cycles) noexcept;

        // --- Stack operations --- 
        //      -- PHA --
        void PHAimplied(u32& Cycles) noexcept;

        //      -- PHP --
        void PHPimplied(u32& Cycles) noexcept;

        //      -- PLA --
        void PLAimplied(u32& Cycles) noexcept;

        //      -- PLP --
        void PLPimplied(u32& Cycles) noexcept;

        //      -- TSX --
        void TSXimplied(u32& Cycles) noexcept;

        //      -- TXS --
        void TXSimplied(u32& Cycles) noexcept;


        // --- Status Flag Changes ---
        //      -- CLC --
        void CLCimplied(u32& Cycles) noexcept;

        //      -- CLD --
        void CLDimplied(u32& Cycles) noexcept;

        //      -- CLI --
        void CLIimplied(u32& Cycles) noexcept;

        //      -- CLV --
        void CLVimplied(u32& Cycles) noexcept;

        //      -- SEC --
        void SECimplied(u32& Cycles) noexcept;

        //      -- SED --
        void SEDimplied(u32& Cycles) noexcept;

        //      -- SEI --
        void SEIimplied(u32& Cycles) noexcept;

        // --- System Functions ---

        //      -- BRK --
        void BRKimplied(u32& Cycles) noexcept;

        //      -- RTI --
        void RTIimplied(u32& Cycles) noexcept;

        //      -- NOP --
        void NOPimplied(u32& Cycles) noexcept;

    public:
        //Processor Status flags
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        
        // 0xFFFE - 0xFFFF - Addres of interrupt vector
        // IRQ - Interrupt request
        static constexpr Word IRQ = 0xFFFE;

        // Stack memory begin
        static constexpr u32 STACK_BEGIN = 0x0100;
        // Stack memory end
        static constexpr u32 STACK_END = 0x01FF;

        CPU() = delete;
        CPU(const CPU&) = delete;
        CPU(CPU&&) = delete;
        explicit CPU(cpu6502::Memory& memory) noexcept;

        ~CPU() = default;

        [[nodiscard]] const cpu6502::Registers& get_registers() const noexcept;

        [[nodiscard]] cpu6502::Registers& get_registers() noexcept;
        
        void reset() noexcept;

        void execute(u32 Cycles);
    };


}


#endif
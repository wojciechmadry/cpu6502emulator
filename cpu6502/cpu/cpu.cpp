#include "cpu.hpp"
#include "exceptions/cpu_except.hpp"

namespace cpu6502{
    //Look up table to all instruction function
   // std::array<CPU::Func* , 256> CPU::LookUpTable; // remove this
   // bool CPU::LookUpTableInit = false;  // remove this

    void CPU::reset() noexcept
    {
        cpu_reg.PC.set(0xFFFA);
        cpu_reg.SP.set(0xFF);
        cpu_reg.PS.put_byte(0x00);
        cpu_reg.ACU.set(0);
        cpu_reg.IRX.set(0);
        cpu_reg.IRY.set(0);
        mem.get().initialise();
    }

    CPU::CPU(cpu6502::Memory &memory) noexcept: mem(memory)
    {
        reset();
       /* if (!LookUpTableInit)  // remove this
        {
            _init();
            LookUpTableInit = true;
        }*/
    }

    void CPU::execute(u32 Cycles)
    {
        // Translate opcode to Byte
        auto op = []<typename Opcode>(Opcode opcode)
        {
            return static_cast<Byte>(opcode);
        };

        while ( Cycles > 0 )
        {
            u32 OldCycles = Cycles;

            Byte ins = fetch_byte(Cycles);

            //LookUpTable[ins](Cycles, *this); // remove this

            switch(ins)
            {
                case op(opcode::ADC::Immediate):
                {
                    ADCimmediate(Cycles);
                    break;
                }
                case op(opcode::ADC::ZeroPage):
                {
                    ADCzeropage(Cycles);
                    break;
                }
                case op(opcode::ADC::ZeroPageX):
                {
                    ADCzeropagex(Cycles);
                    break;
                }
                case op(opcode::ADC::Absolute):
                {
                    ADCabsolute(Cycles);
                    break;
                }
                case op(opcode::ADC::AbsoluteX):
                {
                    ADCabsolutex(Cycles);
                    break;
                }
                case op(opcode::ADC::AbsoluteY):
                {
                    ADCabsolutey(Cycles);
                    break;
                }
                case op(opcode::ADC::IndirectX):
                {
                    ADCindirectx(Cycles);
                    break;
                }
                case op(opcode::ADC::IndirectY):
                {
                    ADCindirecty(Cycles);
                    break;
                }
                case op(opcode::CMP::Immediate):
                {
                    CMPimmediate(Cycles);
                    break;
                }
                case op(opcode::CMP::ZeroPage):
                {
                    CMPzeropage(Cycles);
                    break;
                }
                case op(opcode::CMP::ZeroPageX):
                {
                    CMPzeropagex(Cycles);
                    break;
                }
                case op(opcode::CMP::Absolute):
                {
                    CMPabsolute(Cycles);
                    break;
                }
                case op(opcode::CMP::AbsoluteX):
                {
                    CMPabsolutex(Cycles);
                    break;
                }
                case op(opcode::CMP::AbsoluteY):
                {
                    CMPabsolutey(Cycles);
                    break;
                }
                case op(opcode::CMP::IndirectX):
                {
                    CMPindirectx(Cycles);
                    break;
                }
                case op(opcode::CMP::IndirectY):
                {
                    CMPindirecty(Cycles);
                    break;
                }
                case op(opcode::CPX::Immediate):
                {
                    CPXimmediate(Cycles);
                    break;
                }
                case op(opcode::CPX::Absolute):
                {
                    CPXabsolute(Cycles);
                    break;
                }
                case op(opcode::CPX::ZeroPage):
                {
                    CPXzeropage(Cycles);
                    break;
                }
                case op(opcode::CPY::Immediate):
                {
                    CPYimmediate(Cycles);
                    break;
                }
                case op(opcode::CPY::Absolute):
                {
                    CPYabsolute(Cycles);
                    break;
                }
                case op(opcode::CPY::ZeroPage):
                {
                    CPYzeropage(Cycles);
                    break;
                }
                case op(opcode::SBC::Immediate):
                {
                    SBCimmediate(Cycles);
                    break;
                }
                case op(opcode::SBC::ZeroPage):
                {
                    SBCzeropage(Cycles);
                    break;
                }
                case op(opcode::SBC::ZeroPageX):
                {
                    SBCzeropagex(Cycles);
                    break;
                }
                case op(opcode::SBC::Absolute):
                {
                    SBCabsolute(Cycles);
                    break;
                }
                case op(opcode::SBC::AbsoluteX):
                {
                    SBCabsolutex(Cycles);
                    break;
                }
                case op(opcode::SBC::AbsoluteY):
                {
                    SBCabsolutey(Cycles);
                    break;
                }
                case op(opcode::SBC::IndirectX):
                {
                    SBCindirectx(Cycles);
                    break;
                }
                case op(opcode::SBC::IndirectY):
                {
                    SBCindirecty(Cycles);
                    break;
                }
                case op(opcode::BCC::Relative):
                {
                    BRANCHbcc(Cycles);
                    break;
                }
                case op(opcode::BCS::Relative):
                {
                    BRANCHbcs(Cycles);
                    break;
                }
                case op(opcode::BEQ::Relative):
                {
                    BRANCHbeq(Cycles);
                    break;
                }
                case op(opcode::BMI::Relative):
                {
                    BRANCHbmi(Cycles);
                    break;
                }
                case op(opcode::BNE::Relative):
                {
                    BRANCHbne(Cycles);
                    break;
                }
                case op(opcode::BPL::Relative):
                {
                    BRANCHbpl(Cycles);
                    break;
                }
                case op(opcode::BVC::Relative):
                {
                    BRANCHbvc(Cycles);
                    break;
                }
                case op(opcode::BVS::Relative):
                {
                    BRANCHbvs(Cycles);
                    break;
                }
                default:
                {
                    throw cpu6502::exceptions::bad_instruction{ins};
                    break;
                }
            }

            if (Cycles >= OldCycles)
            {
                throw cpu6502::exceptions::infinite_loop{};
            }

        }
    }

/*  remove this
    void CPU::_init() noexcept
    {
        BRANCHES();
        LDA();
        LDX();
        JSR();
        JMP();
        RTS();
        LDY();
        STA();
        STX();
        STY();
        CLC();
        CLD();
        CLI();
        CLV();
        SEC();
        SED();
        SEI();
        TAX();
        TAY();
        TXA();
        TYA();
        TSX();
        TXS();
        PHA();
        PHP();
        PLA();
        PLP();
        AND();
        EOR();
        ORA();
        BIT();
        ADC();
        CMP();
        CPX();
        CPY();
        SBC();
    }
    */
}
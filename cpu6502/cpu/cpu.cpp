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
        auto op = []<typename Opcode>(const Opcode opcode)
        {
            return static_cast<Byte>(opcode);
        };

        while ( Cycles > 0 )
        {
            const u32 OldCycles = Cycles;

            const Byte ins = fetch_byte(Cycles);

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
                case op(opcode::JMP::Absolute):
                {
                    JMPabsolute(Cycles);
                    break;
                }
                case op(opcode::JMP::Indirect):
                {
                    JMPindirect(Cycles);
                    break;
                }
                case op(opcode::JSR::Absolute):
                {
                    JSRabsolute(Cycles);
                    break;
                }
                case op(opcode::RTS::Implied):
                {
                    RTSimplied(Cycles);
                    break;
                }
                case op(opcode::LDA::Immediate):
                {
                    LDAimmediate(Cycles);
                    break;
                }
                case op(opcode::LDA::ZeroPage):
                {
                    LDAzeropage(Cycles);
                    break;
                }
                case op(opcode::LDA::ZeroPageX):
                {
                    LDAzeropagex(Cycles);
                    break;
                }
                case op(opcode::LDA::Absolute):
                {
                    LDAabsolute(Cycles);
                    break;
                }
                case op(opcode::LDA::AbsoluteX):
                {
                    LDAabsolutex(Cycles);
                    break;
                }
                case op(opcode::LDA::AbsoluteY):
                {
                    LDAabsolutey(Cycles);
                    break;
                }
                case op(opcode::LDA::IndirectX):
                {
                    LDAindirectx(Cycles);
                    break;
                }
                case op(opcode::LDA::IndirectY):
                {
                    LDAindirecty(Cycles);
                    break;
                }
                case op(opcode::LDX::Immediate):
                {
                    LDXimmediate(Cycles);
                    break;
                }
                case op(opcode::LDX::ZeroPage):
                {
                    LDXzeropage(Cycles);
                    break;
                }
                case op(opcode::LDX::ZeroPageY):
                {
                    LDXzeropagey(Cycles);
                    break;
                }       
                case op(opcode::LDX::Absolute):
                {
                    LDXabsolute(Cycles);
                    break;
                }  
                case op(opcode::LDX::AbsoluteY):
                {
                    LDXabsolutey(Cycles);
                    break;
                }          
                case op(opcode::LDY::Immediate):
                {
                    LDYimmediate(Cycles);
                    break;
                }          
                case op(opcode::LDY::ZeroPage):
                {
                    LDYzeropage(Cycles);
                    break;
                }       
                case op(opcode::LDY::ZeroPageX):
                {
                    LDYzeropagex(Cycles);
                    break;
                }      
                case op(opcode::LDY::Absolute):
                {
                    LDYabsolute(Cycles);
                    break;
                }      
                case op(opcode::LDY::AbsoluteX):
                {
                    LDYabsolutex(Cycles);
                    break;
                }   
                case op(opcode::STA::ZeroPage):
                {
                    STAzeropage(Cycles);
                    break;
                } 
                case op(opcode::STA::ZeroPageX):
                {
                    STAzeropagex(Cycles);
                    break;
                }     
                case op(opcode::STA::Absolute):
                {
                    STAabsolute(Cycles);
                    break;
                }    
                case op(opcode::STA::AbsoluteX):
                {
                    STAabsolutex(Cycles);
                    break;
                }           
                case op(opcode::STA::AbsoluteY):
                {
                    STAabsolutey(Cycles);
                    break;
                }            
                case op(opcode::STA::IndircetX):
                {
                    STAindirectx(Cycles);
                    break;
                }       
                case op(opcode::STA::IndircetY):
                {
                    STAindirecty(Cycles);
                    break;
                }    
                case op(opcode::STX::ZeroPage):
                {
                    STXzeropage(Cycles);
                    break;
                }     
                case op(opcode::STX::ZeroPageY):
                {
                    STXzeropagey(Cycles);
                    break;
                }      
                case op(opcode::STX::Absolute):
                {
                    STXabsolute(Cycles);
                    break;
                }    
                case op(opcode::STY::ZeroPage):
                {
                    STYzeropage(Cycles);
                    break;
                }     
                case op(opcode::STY::ZeroPageX):
                {
                    STYzeropagex(Cycles);
                    break;
                }      
                case op(opcode::STY::Absolute):
                {
                    STYabsolute(Cycles);
                    break;
                }                    
                case op(opcode::AND::Immediate):
                {
                    ANDimmediate(Cycles);
                    break;
                }        
                case op(opcode::AND::ZeroPage):
                {
                    ANDzeropage(Cycles);
                    break;
                }   
                case op(opcode::AND::ZeroPageX):
                {
                    ANDzeropagex(Cycles);
                    break;
                }         
                case op(opcode::AND::Absolute):
                {
                    ANDabsolute(Cycles);
                    break;
                }     
                case op(opcode::AND::AbsoluteX):
                {
                    ANDabsolutex(Cycles);
                    break;
                }        
                case op(opcode::AND::AbsoluteY):
                {
                    ANDabsolutey(Cycles);
                    break;
                }       
                case op(opcode::AND::IndirectX):
                {
                    ANDindirectx(Cycles);
                    break;
                }   
                case op(opcode::AND::IndirectY):
                {
                    ANDindirecty(Cycles);
                    break;
                }      
                case op(opcode::BIT::ZeroPage):
                {
                    BITzeropage(Cycles);
                    break;
                }   
                case op(opcode::BIT::Absolute):
                {
                    BITabsolute(Cycles);
                    break;
                }   
                case op(opcode::EOR::Immediate):
                {
                    EORimmediate(Cycles);
                    break;
                }     
                case op(opcode::EOR::ZeroPage):
                {
                    EORzeropage(Cycles);
                    break;
                } 
                case op(opcode::EOR::ZeroPageX):
                {
                    EORzeropagex(Cycles);
                    break;
                }      
                case op(opcode::EOR::Absolute):
                {
                    EORabsolute(Cycles);
                    break;
                }  
                case op(opcode::EOR::AbsoluteX):
                {
                    EORabsolutex(Cycles);
                    break;
                }        
                case op(opcode::EOR::AbsoluteY):
                {
                    EORabsolutey(Cycles);
                    break;
                } 
                case op(opcode::EOR::IndirectX):
                {
                    EORindirectx(Cycles);
                    break;
                }
                case op(opcode::EOR::IndirectY):
                {
                    EORindirecty(Cycles);
                    break;
                }   
                case op(opcode::ORA::Immediate):
                {
                    ORAimmediate(Cycles);
                    break;
                }   
                case op(opcode::ORA::ZeroPage):
                {
                    ORAzeropage(Cycles);
                    break;
                }  
                case op(opcode::ORA::ZeroPageX):
                {
                    ORAzeropagex(Cycles);
                    break;
                }      
                case op(opcode::ORA::Absolute):
                {
                    ORAabsolute(Cycles);
                    break;
                } 
                case op(opcode::ORA::AbsoluteX):
                {
                    ORAabsolutex(Cycles);
                    break;
                }      
                case op(opcode::ORA::AbsoluteY):
                {
                    ORAabsolutey(Cycles);
                    break;
                }        
                case op(opcode::ORA::IndirectX):
                {
                    ORAindirectx(Cycles);
                    break;
                } 
                case op(opcode::ORA::IndirectY):
                {
                    ORAindirecty(Cycles);
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
                throw cpu6502::exceptions::infinite_loop{ins};
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
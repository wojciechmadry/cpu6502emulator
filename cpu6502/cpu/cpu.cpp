#include "cpu.hpp"
#include "exceptions/cpu_except.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace cpu6502{

    CPU::CPU_CLONE_PAIR_TYPE CPU::clone() const noexcept
    {
        auto mem_cpy = std::make_unique<Memory>(this->mem.get());
        auto cpu_cpy = std::make_unique<CPU>(*mem_cpy);
        cpu_cpy->cpu_reg = this->cpu_reg;
        return std::make_pair(std::move(cpu_cpy), std::move(mem_cpy));
    }

    [[nodiscard]] Memory& CPU::get_memory() noexcept
    {
        return mem.get();
    }

    [[nodiscard]] const Memory& CPU::get_memory() const noexcept
    {
        return mem.get();
    }

    cpu6502::Byte CPU::fetch_immediate(cpu6502::u32& Cycles) noexcept
    {
        return fetch_byte(Cycles); // 1 cycles
    }

    cpu6502::Byte CPU::fetch_absolute(cpu6502::u32& Cycles) noexcept
    {
        const Word address = fetch_word(Cycles);
        return read_byte(address, Cycles);
    }

    cpu6502::Byte CPU::fetch_absolutex(cpu6502::u32& Cycles) noexcept
    {
        Word address = fetch_word(Cycles);
        const auto OldAddress = address;
        address += cpu_reg.IRX.get();
        if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
        return read_byte(address, Cycles);
    }

    cpu6502::Byte CPU::fetch_absolutey(cpu6502::u32& Cycles) noexcept
    {
        Word address = fetch_word(Cycles);
        const auto OldAddress = address;
        address += cpu_reg.IRY.get();
        if ((address >> 8) != (OldAddress>>8))
                --Cycles; // 1 cycles if page crossed
        return read_byte(address, Cycles);
    }

    cpu6502::Byte CPU::fetch_indirectx(cpu6502::u32& Cycles) noexcept
    {
        Byte address = fetch_byte(Cycles);
        address += cpu_reg.IRX.get();
        --Cycles;
        const Word TargetAddress = read_word(address, Cycles);
        return read_byte(TargetAddress, Cycles);
    }

    cpu6502::Byte CPU::fetch_indirecty(cpu6502::u32& Cycles) noexcept
    {
        const Byte address = fetch_byte(Cycles);
        Word TargetAddress = read_word(address, Cycles);
        const auto OldAddress = TargetAddress;
        TargetAddress += cpu_reg.IRY.get();
        if ((TargetAddress >> 8) != (OldAddress>>8))
            --Cycles; // 1 cycles if page crossed
        return  read_byte(TargetAddress, Cycles);
    }

    cpu6502::Byte CPU::fetch_zeropage(cpu6502::u32& Cycles) noexcept
    {
        // 2 cycles
        const auto ZeroPageAddress = fetch_byte(Cycles);
        // 1 cycles
        return read_byte(ZeroPageAddress, Cycles);
    }

    cpu6502::Byte CPU::fetch_zeropagex(cpu6502::u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles;
        ZeroPageAddress += cpu_reg.IRX.get();
        --Cycles;
        // 1 cycles
        return read_byte(ZeroPageAddress, Cycles);
    }

    cpu6502::Byte CPU::fetch_zeropagey(cpu6502::u32& Cycles) noexcept
    {
        // 3 cycles
        Byte ZeroPageAddress = fetch_byte(Cycles);
        // 2 cycles;
        ZeroPageAddress += cpu_reg.IRY.get();
        --Cycles;
        // 1 cycles
        return read_byte(ZeroPageAddress, Cycles);
    }

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
    }

    const cpu6502::Registers& CPU::get_registers() const noexcept
    {
        return cpu_reg;
    }

    cpu6502::Registers& CPU::get_registers() noexcept
    {
        return cpu_reg;
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
                case op(opcode::TAX::Implied):
                {
                    TAXimplied(Cycles);
                    break;
                }
                case op(opcode::TAY::Implied):
                {
                    TAYimplied(Cycles);
                    break;
                }
                case op(opcode::TXA::Implied):
                {
                    TXAimplied(Cycles);
                    break;
                } 
                case op(opcode::TYA::Implied):
                {
                    TYAimplied(Cycles);
                    break;
                }   
                case op(opcode::PHA::Implied):
                {
                    PHAimplied(Cycles);
                    break;
                }  
                case op(opcode::PHP::Implied):
                {
                    PHPimplied(Cycles);
                    break;
                }
                case op(opcode::PLA::Implied):
                {
                    PLAimplied(Cycles);
                    break;
                }  
                case op(opcode::PLP::Implied):
                {
                    PLPimplied(Cycles);
                    break;
                }   
                case op(opcode::TSX::Implied):
                {
                    TSXimplied(Cycles);
                    break;
                }
                case op(opcode::TXS::Implied):
                {
                    TXSimplied(Cycles);
                    break;
                } 
                case op(opcode::CLC::Implied):
                {
                    CLCimplied(Cycles);
                    break;
                }  
                case op(opcode::CLD::Implied):
                {
                    CLDimplied(Cycles);
                    break;
                }    
                case op(opcode::CLI::Implied):
                {
                    CLIimplied(Cycles);
                    break;
                } 
                case op(opcode::CLV::Implied):
                {
                    CLVimplied(Cycles);
                    break;
                } 
                case op(opcode::SEC::Implied):
                {
                    SECimplied(Cycles);
                    break;
                }   
                case op(opcode::SED::Implied):
                {
                    SEDimplied(Cycles);
                    break;
                }   
                case op(opcode::SEI::Implied):
                {
                    SEIimplied(Cycles);
                    break;
                }    
                case op(opcode::BRK::Implied):
                {
                    BRKimplied(Cycles);
                    break;
                }     
                case op(opcode::NOP::Implied):
                {
                    NOPimplied(Cycles);
                    break;
                }    
                case op(opcode::RTI::Implied):
                {
                    RTIimplied(Cycles);
                    break;
                }
                case op(opcode::LSR::Accumulator):
                {
                    LSRaccumulator(Cycles);
                    break;
                }
                case op(opcode::LSR::ZeroPage):
                {
                    LSRzeropage(Cycles);
                    break;
                }
                case op(opcode::LSR::ZeroPageX):
                {
                    LSRzeropagex(Cycles);
                    break;
                }          
                case op(opcode::LSR::Absolute):
                {
                    LSRabsolute(Cycles);
                    break;
                }      
                case op(opcode::LSR::AbsoluteX):
                {
                    LSRabsolutex(Cycles);
                    break;
                }             
                case op(opcode::ROL::Accumulator):
                {
                    ROLaccumulator(Cycles);
                    break;
                }   
                case op(opcode::ROL::ZeroPage):
                {
                    ROLzeropage(Cycles);
                    break;
                }  
                case op(opcode::ROL::ZeroPageX):
                {
                    ROLzeropagex(Cycles);
                    break;
                }            
                case op(opcode::ROL::Absolute):
                {
                    ROLabsolute(Cycles);
                    break;
                }       
                case op(opcode::ROL::AbsoluteX):
                {
                    ROLabsolutex(Cycles);
                    break;
                }          
                case op(opcode::ROR::Accumulator):
                {
                    RORaccumulator(Cycles);
                    break;
                }   
                case op(opcode::ROR::ZeroPage):
                {
                    RORzeropage(Cycles);
                    break;
                }  
                case op(opcode::ROR::ZeroPageX):
                {
                    RORzeropagex(Cycles);
                    break;
                }            
                case op(opcode::ROR::Absolute):
                {
                    RORabsolute(Cycles);
                    break;
                }       
                case op(opcode::ROR::AbsoluteX):
                {
                    RORabsolutex(Cycles);
                    break;
                }    
                case op(opcode::ASL::Accumulator):
                {
                    ASLaccumulator(Cycles);
                    break;
                } 
                case op(opcode::ASL::ZeroPage):
                {
                    ASLzeropage(Cycles);
                    break;
                }     
                case op(opcode::ASL::ZeroPageX):
                {
                    ASLzeropagex(Cycles);
                    break;
                }           
                case op(opcode::ASL::Absolute):
                {
                    ASLabsolute(Cycles);
                    break;
                }             
                case op(opcode::ASL::AbsoluteX):
                {
                    ASLabsolutex(Cycles);
                    break;
                }   
                case op(opcode::INC::Absolute):
                {
                    INCabsolute(Cycles);
                    break;
                } 
                case op(opcode::INC::AbsoluteX):
                {
                    INCabsolutex(Cycles);
                    break;
                }         
                case op(opcode::INC::ZeroPage):
                {
                    INCzeropage(Cycles);
                    break;
                } 
                case op(opcode::INC::ZeroPageX):
                {
                    INCzeropagex(Cycles);
                    break;
                }     
                case op(opcode::DEC::Absolute):
                {
                    DECabsolute(Cycles);
                    break;
                } 
                case op(opcode::DEC::AbsoluteX):
                {
                    DECabsolutex(Cycles);
                    break;
                }         
                case op(opcode::DEC::ZeroPage):
                {
                    DECzeropage(Cycles);
                    break;
                } 
                case op(opcode::DEC::ZeroPageX):
                {
                    DECzeropagex(Cycles);
                    break;
                } 
                case op(opcode::INX::Implied):
                {
                    INXimplied(Cycles);
                    break;
                }  
                case op(opcode::INY::Implied):
                {
                    INYimplied(Cycles);
                    break;
                }   
                case op(opcode::DEX::Implied):
                {
                    DEXimplied(Cycles);
                    break;
                }                                                                              
                case op(opcode::DEY::Implied):
                {
                    DEYimplied(Cycles);
                    break;
                }
                 case op(opcode::MUL::Immediate):
                {
                    MULimmediate(Cycles);
                    break;
                }
                case op(opcode::MUL::ZeroPage):
                {
                    MULzeropage(Cycles);
                    break;
                }
                case op(opcode::MUL::ZeroPageX):
                {
                    MULzeropagex(Cycles);
                    break;
                }
                case op(opcode::MUL::Absolute):
                {
                    MULabsolute(Cycles);
                    break;
                }
                case op(opcode::MUL::AbsoluteX):
                {
                    MULabsolutex(Cycles);
                    break;
                }
                case op(opcode::MUL::AbsoluteY):
                {
                    MULabsolutey(Cycles);
                    break;
                }
                case op(opcode::MUL::IndirectX):
                {
                    MULindirectx(Cycles);
                    break;
                }
                case op(opcode::MUL::IndirectY):
                {
                    MULindirecty(Cycles);
                    break;
                }
                case 0xFF:
                {   
                    // There is no instruction left, end executing
                    Cycles = 0;
                    cpu_reg.PC.decrement();
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
    
}
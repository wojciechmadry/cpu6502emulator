#include "interp_utils.hpp"
#include "fmt/core.h"

#include <set>

namespace cpu6502::interpreter::utils
{
    // Static unordered_map of all opcodes
    const std::unordered_map<std::string, InstructionInfo>& get_opcode_map()
    {
        auto push_address = [](InstructionInfo& II, Addressing mode, int op)
        {
            InstructionInfo::SmallAddressInfo sAi;
            sAi.set_mode(mode);
            sAi.set_op_code(op);
            II.add_address(sAi);
        };

        static bool MAP_IS_INITIALISED = false;
        static std::unordered_map<std::string, InstructionInfo> map_of_operations;

        // Init map of addressing opcode
        if(MAP_IS_INITIALISED == false)
        {
            auto safe_insert = [&]<typename INSTRUCTION_INFO>
            (std::string key, INSTRUCTION_INFO&& val)
            requires (std::is_same_v<std::decay_t<INSTRUCTION_INFO>, InstructionInfo>)
            {
                for(auto& c : key)
                {
                    c = static_cast<char>(std::toupper(static_cast<int>(c)));
                }
                const auto found = map_of_operations.find(key);
                if(found != map_of_operations.end())
                {
                    fmt::print("Instruction '{}' already exist!\n", key);
                }
                else
                {
                    map_of_operations[std::move(key)] = std::forward<INSTRUCTION_INFO>(val);
                }
            };

            // Init INC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::ZeroPage, 0xE6);
                push_address(ii, Addressing::ZeroPageX, 0xF6);
                push_address(ii, Addressing::Absolute, 0xEE);
                push_address(ii, Addressing::AbsoluteX, 0xFE);
                safe_insert("INC", std::move(ii));
            }

            // Init INX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xE8);
                safe_insert("INX", std::move(ii));
            }

            // Init INY
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xC8);
                safe_insert("INY", std::move(ii));
            }

            // Init DEC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::ZeroPage, 0xC6);
                push_address(ii, Addressing::ZeroPageX, 0xD6);
                push_address(ii, Addressing::Absolute, 0xCE);
                push_address(ii, Addressing::AbsoluteX, 0xDE);
                safe_insert("DEC", std::move(ii));
            }

            // Init DEX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xCA);
                safe_insert("DEX", std::move(ii));
            }

            // Init DEY
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x88);
                safe_insert("DEY", std::move(ii));
            }

            // Init LSR
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Accumulator, 0x4A);
                push_address(ii, Addressing::ZeroPage, 0x46);
                push_address(ii, Addressing::ZeroPageX, 0x56);
                push_address(ii, Addressing::Absolute, 0x4E);
                push_address(ii, Addressing::AbsoluteX, 0x5E);
                safe_insert("LSR", std::move(ii));
            }

            // Init ASL
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Accumulator, 0x0A);
                push_address(ii, Addressing::ZeroPage, 0x06);
                push_address(ii, Addressing::ZeroPageX, 0x16);
                push_address(ii, Addressing::Absolute, 0x0E);
                push_address(ii, Addressing::AbsoluteX, 0x1E);
                safe_insert("ASL", std::move(ii));
            }

            // Init ROL
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Accumulator, 0x2A);
                push_address(ii, Addressing::ZeroPage, 0x26);
                push_address(ii, Addressing::ZeroPageX, 0x36);
                push_address(ii, Addressing::Absolute, 0x2E);
                push_address(ii, Addressing::AbsoluteX, 0x3E);
                safe_insert("ROL", std::move(ii));
            }

            // Init ROR
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Accumulator, 0x6A);
                push_address(ii, Addressing::ZeroPage, 0x66);
                push_address(ii, Addressing::ZeroPageX, 0x76);
                push_address(ii, Addressing::Absolute, 0x6E);
                push_address(ii, Addressing::AbsoluteX, 0x7E);
                safe_insert("ROR", std::move(ii));
            }

            // Init BRK
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x00);
                safe_insert("BRK", std::move(ii));
            }

            // Init NOP
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xEA);
                safe_insert("NOP", std::move(ii));
            }

            // Init RTI
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x40);
                safe_insert("RTI", std::move(ii));
            }

            // Init ADC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0x69);
                push_address(ii, Addressing::ZeroPage, 0x65);
                push_address(ii, Addressing::ZeroPageX, 0x75);
                push_address(ii, Addressing::Absolute, 0x6D);
                push_address(ii, Addressing::AbsoluteX, 0x7D);
                push_address(ii, Addressing::AbsoluteY, 0x79);
                push_address(ii, Addressing::IndirectX, 0x61);
                push_address(ii, Addressing::IndirectY, 0x71);
                safe_insert("ADC", std::move(ii));
            }

            // Init MUL
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0x89);
                push_address(ii, Addressing::ZeroPage, 0x77);
                push_address(ii, Addressing::ZeroPageX, 0x74);
                push_address(ii, Addressing::Absolute, 0x6F);
                push_address(ii, Addressing::AbsoluteX, 0x7F);
                push_address(ii, Addressing::AbsoluteY, 0x7A);
                push_address(ii, Addressing::IndirectX, 0x62);
                push_address(ii, Addressing::IndirectY, 0x63);
                safe_insert("MUL", std::move(ii));
            }

            // Init SBC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xE9);
                push_address(ii, Addressing::ZeroPage, 0xE5);
                push_address(ii, Addressing::ZeroPageX, 0xF5);
                push_address(ii, Addressing::Absolute, 0xED);
                push_address(ii, Addressing::AbsoluteX, 0xFD);
                push_address(ii, Addressing::AbsoluteY, 0xF9);
                push_address(ii, Addressing::IndirectX, 0xE1);
                push_address(ii, Addressing::IndirectY, 0xF1);
                safe_insert("SBC", std::move(ii));
            }

            // Init CMP
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xC9);
                push_address(ii, Addressing::ZeroPage, 0xC5);
                push_address(ii, Addressing::ZeroPageX, 0xD5);
                push_address(ii, Addressing::Absolute, 0xCD);
                push_address(ii, Addressing::AbsoluteX, 0xDD);
                push_address(ii, Addressing::AbsoluteY, 0xD9);
                push_address(ii, Addressing::IndirectX, 0xC1);
                push_address(ii, Addressing::IndirectY, 0xD1);
                safe_insert("CMP", std::move(ii));
            }

            // Init CPX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xE0);
                push_address(ii, Addressing::ZeroPage, 0xE4);
                push_address(ii, Addressing::Absolute, 0xEC);
                safe_insert("CPX", std::move(ii));
            }

            // Init CPY
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xC0);
                push_address(ii, Addressing::ZeroPage, 0xC4);
                push_address(ii, Addressing::Absolute, 0xCC);
                safe_insert("CPY", std::move(ii));
            }

            // Init LDA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xA9);
                push_address(ii, Addressing::ZeroPage, 0xA5);
                push_address(ii, Addressing::ZeroPageX, 0xB5);
                push_address(ii, Addressing::Absolute, 0xAD);
                push_address(ii, Addressing::AbsoluteX, 0xBD);
                push_address(ii, Addressing::AbsoluteY, 0xB9);
                push_address(ii, Addressing::IndirectX, 0xA1);
                push_address(ii, Addressing::IndirectY, 0xB1);
                safe_insert("LDA", std::move(ii));
            }

            // Init LDX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xA2);
                push_address(ii, Addressing::ZeroPage, 0xA6);
                push_address(ii, Addressing::ZeroPageY, 0xB6);
                push_address(ii, Addressing::Absolute, 0xAE);
                push_address(ii, Addressing::AbsoluteY, 0xBE);
                safe_insert("LDX", std::move(ii));
            }

            // Init LDY
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0xA0);
                push_address(ii, Addressing::ZeroPage, 0xA4);
                push_address(ii, Addressing::ZeroPageX, 0xB4);
                push_address(ii, Addressing::Absolute, 0xAC);
                push_address(ii, Addressing::AbsoluteX, 0xBC);
                safe_insert("LDY", std::move(ii));
            }

            // Init STA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::ZeroPage, 0x85);
                push_address(ii, Addressing::ZeroPageX, 0x95);
                push_address(ii, Addressing::Absolute, 0x8D);
                push_address(ii, Addressing::AbsoluteX, 0x9D);
                push_address(ii, Addressing::AbsoluteY, 0x99);
                push_address(ii, Addressing::IndirectX, 0x81);
                push_address(ii, Addressing::IndirectY, 0x91);
                safe_insert("STA", std::move(ii));
            }

            // Init STX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::ZeroPage, 0x86);
                push_address(ii, Addressing::ZeroPageY, 0x96);
                push_address(ii, Addressing::Absolute, 0x8E);
                safe_insert("STX", std::move(ii));
            }

            // Init STY
            {
                InstructionInfo ii;
                push_address(ii, Addressing::ZeroPage, 0x84);
                push_address(ii, Addressing::ZeroPageX, 0x94);
                push_address(ii, Addressing::Absolute, 0x8C);
                safe_insert("STY", std::move(ii));
            }

            // Init JSR
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Absolute, 0x20);
                safe_insert("JSR", std::move(ii));
            }

            // Init JMP
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Absolute, 0x4C);
                push_address(ii, Addressing::Indirect, 0x6C);
                safe_insert("JMP", std::move(ii));
            }

            // Init RTS
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x60);
                safe_insert("RTS", std::move(ii));
            }

            // Init CLC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x18);
                safe_insert("CLC", std::move(ii));
            }

            // Init CLD
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xD8);
                safe_insert("CLD", std::move(ii));
            }

            // Init CLI
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x58);
                safe_insert("CLI", std::move(ii));
            }

            // Init CLV
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xB8);
                safe_insert("CLV", std::move(ii));
            }

            // Init SEC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x38);
                safe_insert("SEC", std::move(ii));
            }

            // Init SED
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xF8);
                safe_insert("SED", std::move(ii));
            }

            // Init SEI
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x78);
                safe_insert("SEI", std::move(ii));
            }

            // Init TAX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xAA);
                safe_insert("TAX", std::move(ii));
            }

            // Init TAY
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xA8);
                safe_insert("TAY", std::move(ii));
            }

            // Init TXA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x8A);
                safe_insert("TXA", std::move(ii));
            }

            // Init TYA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x98);
                safe_insert("TYA", std::move(ii));
            }

            // Init TSX
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0xBA);
                safe_insert("TSX", std::move(ii));
            }

            // Init TXS
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x9A);
                safe_insert("TXS", std::move(ii));
            }

            // Init PHA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x48);
                safe_insert("PHA", std::move(ii));
            }

            // Init PHP
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x08);
                safe_insert("PHP", std::move(ii));
            }

            // Init PLA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x68);
                safe_insert("PLA", std::move(ii));
            }

            // Init PLP
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Implicit, 0x28);
                safe_insert("PLP", std::move(ii));
            }

            // Init AND
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0x29);
                push_address(ii, Addressing::ZeroPage, 0x25);
                push_address(ii, Addressing::ZeroPageX, 0x35);
                push_address(ii, Addressing::Absolute, 0x2D);
                push_address(ii, Addressing::AbsoluteX, 0x3D);
                push_address(ii, Addressing::AbsoluteY, 0x39);
                push_address(ii, Addressing::IndirectX, 0x21);
                push_address(ii, Addressing::IndirectY, 0x31);
                safe_insert("AND", std::move(ii));
            }

            // Init EOR
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0x49);
                push_address(ii, Addressing::ZeroPage, 0x45);
                push_address(ii, Addressing::ZeroPageX, 0x55);
                push_address(ii, Addressing::Absolute, 0x4D);
                push_address(ii, Addressing::AbsoluteX, 0x5D);
                push_address(ii, Addressing::AbsoluteY, 0x59);
                push_address(ii, Addressing::IndirectX, 0x41);
                push_address(ii, Addressing::IndirectY, 0x51);
                safe_insert("EOR", std::move(ii));
            }

            // Init ORA
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Immediate, 0x09);
                push_address(ii, Addressing::ZeroPage, 0x05);
                push_address(ii, Addressing::ZeroPageX, 0x15);
                push_address(ii, Addressing::Absolute, 0x0D);
                push_address(ii, Addressing::AbsoluteX, 0x1D);
                push_address(ii, Addressing::AbsoluteY, 0x19);
                push_address(ii, Addressing::IndirectX, 0x01);
                push_address(ii, Addressing::IndirectY, 0x11);
                safe_insert("ORA", std::move(ii));
            }

            // Init BIT
            {
                InstructionInfo ii;
                push_address(ii, Addressing::ZeroPage, 0x24);
                push_address(ii, Addressing::Absolute, 0x2C);
                safe_insert("BIT", std::move(ii));
            }

            // Init BCC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0x90);
                safe_insert("BCC", std::move(ii));
            }
            
            // Init BCS
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0xB0);
                safe_insert("BCS", std::move(ii));
            }

            // Init BEQ
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0xF0);
                safe_insert("BEQ", std::move(ii));
            }

            // Init BMI
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0x30);
                safe_insert("BMI", std::move(ii));
            }

            // Init BNE
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0xD0);
                safe_insert("BNE", std::move(ii));
            }

            // Init BPL
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0x10);
                safe_insert("BPL", std::move(ii));
            }

            // Init BVC
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0x50);
                safe_insert("BVC", std::move(ii));
            }

            // Init BVS
            {
                InstructionInfo ii;
                push_address(ii, Addressing::Relative, 0x70);
                safe_insert("BVS", std::move(ii));
            }


            // Check if all address are unique
            {
                std::set<int> all_opcodes;
                for(const auto& [id, value]: map_of_operations)
                {
                    const auto& vec = value.get_addressing_vector();
                    for(const auto& ai : vec)
                    {
                        const auto& opcode = ai.get_op_code();
                        if(all_opcodes.contains(opcode))
                        {
                            fmt::print("Opcode '0x{:X}' of instruction '{}' already exist!\n", opcode, id);
                            exit(1);
                        }   
                        else
                        {
                            all_opcodes.insert(opcode);
                        }
                    }
                }
            }
            MAP_IS_INITIALISED = true;
        }
        return map_of_operations;
    }
}

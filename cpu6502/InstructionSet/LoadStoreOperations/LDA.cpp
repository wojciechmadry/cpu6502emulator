#include "cpu.hpp"

namespace cpu6502 {
    [[nodiscard]] bool CPU::LDA(Byte Opcode, u32 &Cycles) noexcept {
        using LDAop = cpu6502::opcode::LDA;
        switch (static_cast<LDAop>(Opcode)) {
            case LDAop::Immediate: {
                cpu_reg.ACU.set(fetch_byte(Cycles));
            }
                break;
            case LDAop::ZeroPage: {
                Byte ZeroPageAddress = fetch_byte(Cycles);
                cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));
            }
                break;
            case LDAop::ZeroPageX: {
                Byte ZeroPageAddress = fetch_byte(Cycles);
                ZeroPageAddress += cpu_reg.IRX.get();
                --Cycles;
                cpu_reg.ACU.set(read_byte(ZeroPageAddress, Cycles));
            }
                break;
            case LDAop::Absolute: {
                Word address = fetch_word(Cycles);
                cpu_reg.ACU.set(read_byte(address, Cycles));
            }
                break;
            case LDAop::AbsoluteX: {
                Word address = fetch_word(Cycles);
                address += cpu_reg.IRX.get();
                if (cpu_reg.IRX.get() != 0)
                    --Cycles;
                cpu_reg.ACU.set(read_byte(address, Cycles));
            }
                break;
            case LDAop::AbsoluteY: {
                Word address = fetch_word(Cycles);
                address += cpu_reg.IRY.get();
                if (cpu_reg.IRY.get() != 0)
                    --Cycles;
                cpu_reg.ACU.set(read_byte(address, Cycles));
            }
                break;
            case LDAop::IndirectX: {
                Byte address = fetch_byte(Cycles);
                address += cpu_reg.IRX.get();
                --Cycles;
                Word TargetAddress = read_word(address, Cycles);
                cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));
            }
                break;
            case LDAop::IndirectY: {
                Byte address = fetch_byte(Cycles);
                Word TargetAddress = read_word(address, Cycles);
                TargetAddress += cpu_reg.IRY.get();
                if (cpu_reg.IRY.get() != 0)
                    --Cycles;
                cpu_reg.ACU.set(read_byte(TargetAddress, Cycles));
            }
                break;
            default:
                return false;
        };

        cpu_reg.PS.set(PSFlags::ZeroFlag, !static_cast<bool>(cpu_reg.ACU.get()));
        cpu_reg.PS.set(PSFlags::NegativeFlag, cpu_reg.ACU.get() & 0x80);

        return true;
    }
}

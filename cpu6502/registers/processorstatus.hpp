#ifndef CPU_6502_registers_processorstatus
#define CPU_6502_registers_processorstatus

#include "required.hpp"

namespace cpu6502::registers
{
    class ProcessorStatus
    {
        Byte _reg = 0x00;
    public:
        ProcessorStatus() = default;
        ~ProcessorStatus() = default;

        enum class Flags : Byte
        {
            CarryFlag = 1,
            ZeroFlag = 2,
            InterruptDisable = 4,
            DecimalMode = 8,
            BreakCommand = 16,
            OverflowFlag = 32,
            NegativeFlag = 64
        };

        [[nodiscard]] bool get(const Flags flag) const noexcept
        {
            auto FlagChar = static_cast<uint8_t>(flag);
            return _reg & FlagChar;
        }

        void set(const Flags flag, const bool NewFlagValue) noexcept
        {
            auto FlagChar = static_cast<uint8_t>(flag);
            if (NewFlagValue)
                _reg |= FlagChar;
            else
                _reg = static_cast<decltype(_reg)>(_reg & (~FlagChar));
        }

        void put_byte(const Byte NewRegValue) noexcept
        {
            _reg = NewRegValue;
        }
    };

}

#endif
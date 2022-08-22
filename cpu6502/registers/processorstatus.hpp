#ifndef CPU_6502_registers_processorstatus
#define CPU_6502_registers_processorstatus

#include "../required.hpp"

namespace cpu6502::registers
{
    class ProcessorStatus
    {
        Byte m_reg = 0x00;
    public:

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

        [[nodiscard]] bool get(Flags flag) const noexcept;

        void set(Flags flag,  bool NewFlagValue) noexcept;

        void put_byte(Byte NewRegValue) noexcept;

        [[nodiscard]] Byte pull_byte() const noexcept;

        bool operator==(const ProcessorStatus& other) const noexcept;

    };

}

#endif

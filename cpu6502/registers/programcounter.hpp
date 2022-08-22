#ifndef CPU_6502_registers_programcounter
#define CPU_6502_registers_programcounter

#include "../required.hpp"

namespace cpu6502::registers
{
    class ProgramCounter
    {
        Word m_reg = 0;
    public:
        using RegisterStroedType = decltype(m_reg);

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;

        void increment() noexcept;

        void decrement() noexcept;

        bool operator==(const ProgramCounter& other) const noexcept;
    };
}
#endif

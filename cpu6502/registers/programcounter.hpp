#ifndef CPU_6502_registers_programcounter
#define CPU_6502_registers_programcounter

#include "../required.hpp"

namespace cpu6502::registers
{
    class ProgramCounter
    {
        Word _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
        ProgramCounter() = default;
        ~ProgramCounter() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;

        void increment() noexcept;
    };
}
#endif
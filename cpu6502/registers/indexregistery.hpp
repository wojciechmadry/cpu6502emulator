#ifndef CPU_6502_registers_indexregistery
#define CPU_6502_registers_indexregistery

#include "../required.hpp"

namespace cpu6502::registers
{
    class IndexRegisterY
    {
        Byte _reg = 0;
        using RegisterStroedType = decltype(_reg);
    public:
        IndexRegisterY() = default;
        ~IndexRegisterY() = default;

        [[nodiscard]] RegisterStroedType get() const noexcept;

        [[nodiscard]] RegisterStroedType& get() noexcept;

        void set(RegisterStroedType NewRegValue) noexcept;
    };

}

#endif
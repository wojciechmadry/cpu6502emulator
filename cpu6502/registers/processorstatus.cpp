#include "processorstatus.hpp"


namespace cpu6502::registers{

    [[nodiscard]] bool ProcessorStatus::get(const ProcessorStatus::Flags flag) const noexcept
    {
        auto FlagChar = static_cast<uint8_t>(flag);
        return _reg & FlagChar;
    }

    void ProcessorStatus::set(const ProcessorStatus::Flags flag, const bool NewFlagValue) noexcept
    {
        auto FlagChar = static_cast<uint8_t>(flag);
        if ( NewFlagValue )
            _reg |= FlagChar;
        else
            _reg = static_cast<decltype(_reg)>(_reg & ( ~FlagChar ));
    }

    void ProcessorStatus::put_byte(const Byte NewRegValue) noexcept
    {
        _reg = NewRegValue;
    }

    [[nodiscard]] Byte ProcessorStatus::pull_byte() const noexcept
    {
        return _reg;
    }

}
#include "processorstatus.hpp"


namespace cpu6502::registers{

    [[nodiscard]] bool ProcessorStatus::get(const ProcessorStatus::Flags flag) const noexcept
    {
        const auto FlagChar = static_cast<uint8_t>(flag);
        return m_reg & FlagChar;
    }

    void ProcessorStatus::set(const ProcessorStatus::Flags flag, const bool NewFlagValue) noexcept
    {
        const auto FlagChar = static_cast<uint8_t>(flag);
        if ( NewFlagValue )
            m_reg |= FlagChar;
        else
            m_reg = static_cast<decltype(m_reg)>(m_reg & ( ~FlagChar ));
    }

    void ProcessorStatus::put_byte(const Byte NewRegValue) noexcept
    {
        m_reg = NewRegValue;
    }

    [[nodiscard]] Byte ProcessorStatus::pull_byte() const noexcept
    {
        return m_reg;
    }

    bool ProcessorStatus::operator==(const ProcessorStatus& other) const noexcept
    {
        return m_reg == other.m_reg;
    }

}
#ifndef CPU_6502_TEST_register
#define CPU_6502_TEST_register
#include <cassert>
#include "../cpu6502/registers/registers.hpp"
namespace CPU6502_TEST::inner
{
    bool RUN_REGISTER_TEST() noexcept
    {
        cpu6502::registers::ProcessorStatus ps;
        using flags = cpu6502::registers::ProcessorStatus::Flags;
        assert(
                ps.get(flags::OverflowFlag) == false &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == false
                );
        ps.set(flags::ZeroFlag, true);
        assert(
                ps.get(flags::OverflowFlag) == false &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == true
        );
        ps.set(flags::OverflowFlag, true);
        assert(
                ps.get(flags::OverflowFlag) == true &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == true
        );
        ps.set(flags::ZeroFlag, false);
        assert(
                ps.get(flags::OverflowFlag) == true &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == false
        );
        ps.set(flags::OverflowFlag, false);
        assert(
                ps.get(flags::OverflowFlag) == false &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == false
        );
        return true;
    }
}
#endif
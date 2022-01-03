#include "register_test.hpp"

#include "registers/registers.hpp"

#include "test_logger.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_REGISTER_TEST() noexcept
    {
        bool all_good = true;
        cpu6502::registers::ProcessorStatus ps;
        using flags = cpu6502::registers::ProcessorStatus::Flags;
        all_good &= (
                ps.get(flags::OverflowFlag) == false &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == false
        );
        ps.set(flags::ZeroFlag, true);
        all_good &=(
                ps.get(flags::OverflowFlag) == false &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == true
        );

        ps.set(flags::OverflowFlag, true);
        all_good &=(
                ps.get(flags::OverflowFlag) == true &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == true
        );
        ps.set(flags::ZeroFlag, false);
        all_good &= (
                ps.get(flags::OverflowFlag) == true &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == false
        );
        ps.set(flags::OverflowFlag, false);
        all_good &=(
                ps.get(flags::OverflowFlag) == false &&
                ps.get(flags::BreakCommand) == false &&
                ps.get(flags::InterruptDisable) == false &&
                ps.get(flags::CarryFlag) == false &&
                ps.get(flags::DecimalMode) == false &&
                ps.get(flags::NegativeFlag) == false &&
                ps.get(flags::ZeroFlag) == false
        );

        log_test("REGISTER", all_good);

        return all_good;
    }
}

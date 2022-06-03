#include "instruction.hpp"
#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "processorstatus.hpp"
#include "required.hpp"
#include "utility/utility.hpp"
#include "interpreter.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool ADDRESSING_ACCUMULATOR_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    auto& all_reg = cpu.get_registers();

    constexpr auto acu_val = 0xF;
    utils::jump_to_2020(cpu);
    utils::load_to_acu(cpu, acu_val);

    cpu6502::interpreter::Interpreter interp(cpu);

    auto run_test = [&](const std::string& command, std::uint8_t output) 
    {
        auto& reg = all_reg.ACU;
        bool test_result = true;
        auto addressing = interp.interprete(command);
        test_result &= addressing == cpu6502::interpreter::Addressing::Accumulator;
        test_result &= reg.get() == output;
        reg.get() = acu_val;
        all_good &= test_result;
    };
    // Test correct command

    // asl a
    run_test("asl a", acu_val << 1);

    // ASL A
    run_test("ASL A", acu_val << 1);

    // asl A
    run_test("asl A", acu_val << 1);


    // lsr a
    run_test("lsr a", acu_val >> 1);

    // LSR A
    run_test("LSR A", acu_val >> 1);

    // lsr A
    run_test("lsr A", acu_val >> 1);

    utils::load_to_acu(cpu, 0x16);
    all_good &= cpu6502::interpreter::Addressing::Accumulator == interp.interprete("lsr A");
    all_good &= cpu6502::interpreter::Addressing::Accumulator == interp.interprete("asl A");
    all_good &= cpu6502::interpreter::Addressing::Accumulator == interp.interprete("lsr A");
    all_good &= cpu6502::interpreter::Addressing::Accumulator == interp.interprete("asl A");
    all_good &= 0x16 == all_reg.ACU.get();
    utils::load_to_acu(cpu, acu_val);
    // Test bad command

    auto run_bad_cmd = [&](const std::string& command)
    {
        try
        {
            const auto addressing = interp.interprete(command);
            all_good &= addressing != cpu6502::interpreter::Addressing::Accumulator;
        }
        catch(const std::exception&)
        {
            all_good &= true;
        }
        
    };

    // ad
    run_bad_cmd("ad");

    // adc
    run_bad_cmd("adc");

    // asl
    run_bad_cmd("asl");

    // asl aa
    run_bad_cmd("asl aa");

    // asl b
    run_bad_cmd("asl b");

    return all_good;
}

}  // namespace CPU6502_TEST::interpreter_test::inner

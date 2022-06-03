#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"
#include "interpreter.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool ADDRESSING_ZERO_PAGE_X_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    auto& all_reg = cpu.get_registers();

    utils::jump_to_2020(cpu);

    constexpr cpu6502::Byte IRX_value = 0x10;
    utils::load_to_xreg(cpu, IRX_value);

    cpu6502::interpreter::Interpreter interp(cpu);
    const std::string label_name_good = "ProperAddress";
    const std::string label_name_bad = "BadAddress";

    constexpr std::uint8_t LSB_good = 0x06;
    constexpr std::uint8_t MSB_good = 0x00;
    constexpr std::uint32_t label_value_good = (MSB_good << 8) | LSB_good;

    interp.add_label(label_name_good, label_value_good);

    constexpr std::uint8_t LSB_bad = 0xFF;
    constexpr std::uint8_t MSB_bad = 0xFF;
    constexpr std::uint32_t label_value_bad = (MSB_bad << 8) | LSB_bad;

    interp.add_label(label_name_bad, label_value_bad);

    constexpr cpu6502::Byte zero_page_val = 0x05;

    auto run_test = [&](const std::string& command, std::uint8_t output, auto& reg) 
    {
        bool test_result = true;
        test_result &= reg.get() == 0;
        const auto addressing = interp.interprete(command);
        test_result &= addressing == cpu6502::interpreter::Addressing::ZeroPageX;
        test_result &= reg.get() == output;
        reg.get() = 0;
        all_good &= test_result;
    };

    // Test correct command
    // Write '0x05' to zero page address '0x0006' + IRX
    mem[label_value_good + IRX_value] = zero_page_val;
    mem[0xA + IRX_value] = zero_page_val;
    

    // Test ADC $A, X
    run_test("adc $A, X", zero_page_val, all_reg.ACU);

    // Test ADC $0A, X
    run_test("adc $0A, X", zero_page_val, all_reg.ACU);

    // Test ADC $6, X
    run_test("adc $6, X", zero_page_val, all_reg.ACU);

    // Test ADC $06, X
    run_test("adc $06, X", zero_page_val, all_reg.ACU);

    // Test ADC $6, x
    run_test("adc $6, x", zero_page_val, all_reg.ACU);

    // Test ADC $06, x
    run_test("adc $06, x", zero_page_val, all_reg.ACU);

    // Test ADC ProperAddress, x
    run_test("adc ProperAddress, x", zero_page_val, all_reg.ACU);

    // Test ADC PROPERADDRESS, x
    run_test("adc PROPERADDRESS, x", zero_page_val, all_reg.ACU);

    // Test ADC ProperAddress, x
    run_test("adc ProperAddress, x", zero_page_val, all_reg.ACU);

    // Test ADC PROPERADDRESS, x
    run_test("adc PROPERADDRESS, x", zero_page_val, all_reg.ACU);

    // Test three command in row
    {
        cpu.reset();
        utils::jump_to_2020(cpu);
        utils::load_to_xreg(cpu, IRX_value);
        mem[label_value_good + IRX_value] = zero_page_val;
        auto& reg = cpu.get_registers();
        const std::string cmd1 = "adc ProperAddress, x";
        const std::string cmd2 = "adc $06, x";
        const std::string cmd3 = "adc $6, X";
        interp.interprete(cmd1);
        interp.interprete(cmd2);
        interp.interprete(cmd3);
        all_good &= reg.ACU.get() == zero_page_val * 3;
        reg.ACU.get() = 0;
        cpu.reset();
        utils::jump_to_2020(cpu);
        utils::load_to_xreg(cpu, IRX_value);
    }
        

    // Test bad command

    auto run_bad_cmd = [&](const std::string& command)
    {
        try
        {
            const auto addressing = interp.interprete(command);
            all_good &= addressing != cpu6502::interpreter::Addressing::ZeroPageX;
        }
        catch(const std::exception&)
        {
            all_good &= true;
        }
        
    };

    run_bad_cmd("add 6, X");

    run_bad_cmd("add 06, x");

    run_bad_cmd("add $256, x");

    run_bad_cmd("add label_name_bad, x");

    run_bad_cmd("adc ($00A2,X)");
    
    run_bad_cmd("adc ($00A2,Y)");

    return all_good;
}

}  // namespace CPU6502_TEST::interpreter_test::inner

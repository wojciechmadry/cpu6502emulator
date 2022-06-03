#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"
#include "interpreter.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool ADDRESSING_IMMEDIATE_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    auto& all_reg = cpu.get_registers();

    utils::jump_to_2020(cpu);

    cpu6502::interpreter::Interpreter interp(cpu);

    const std::string label_name = "lAbEl";
    constexpr std::uint8_t LSB = 0x06;
    constexpr std::uint8_t MSB = 0xA3;
    constexpr std::uint32_t label_value = (MSB << 8) | LSB;

    interp.add_label(label_name, label_value);

    auto run_test = [&](const std::string& command, std::uint8_t output, auto& reg) 
    {
        bool test_result = true;
        test_result &= reg.get() == 0;
        auto addressing = interp.interprete(command);
        test_result &= addressing == cpu6502::interpreter::Addressing::Immediate;
        test_result &= reg.get() == output;
        reg.get() = 0;
        all_good &= test_result;
    };
    // Test correct command

    // Test ADC #$AB
    run_test("ADC #$AB", 0xAB, all_reg.ACU);

    // Test ADC #$11
    run_test("ADC #$11", 0x11, all_reg.ACU);

    // Test ADC #%101
    run_test("ADC #%101", 0b101, all_reg.ACU);

    // Test ADC #10
    run_test("ADC #10", 10, all_reg.ACU);

    // Test adc #15
    run_test("adc #15", 15, all_reg.ACU);

    // adc #lo label
    run_test("adc #lo label", LSB, all_reg.ACU);

    // adc #LO label
    run_test("adc #LO label", LSB, all_reg.ACU);

    // adc #LO LABEL
    run_test("adc #LO LABEL", LSB, all_reg.ACU);

    // adc #hi label
    run_test("adc #hi label", MSB, all_reg.ACU);

    // adc #hi LABEL
    run_test("adc #hi LABEL", MSB, all_reg.ACU);

    // adc #HI label
    run_test("adc #HI label", MSB, all_reg.ACU);

    // adc #Hi LaBeL
    run_test("adc #Hi LaBeL", MSB, all_reg.ACU);

    // Test two command in row

    {
        cpu.reset();
        utils::jump_to_2020(cpu);
        auto& reg = cpu.get_registers();
        const std::string cmd1 = "ADC #HI LABEL";
        const std::string cmd2 = "ADC #LO LABEL";
        interp.interprete(cmd1);
        interp.interprete(cmd2);
        all_good &= reg.ACU.get() == LSB + MSB;
        reg.ACU.get() = 0;
        cpu.reset();
        utils::jump_to_2020(cpu);
    }
        

    // Test bad command

    auto run_bad_cmd = [&](const std::string& command)
    {
        try
        {
            interp.interprete(command);
            all_good = false;
        }
        catch(const std::exception&)
        {
            all_good &= true;
        }
        
    };

    // ad #Hi LaBeL
    run_bad_cmd("ad #Hi LaBeL");

    // adc #H LaBeL
    run_bad_cmd("adc #H LaBeL");

    // adc #Hi LaBe
    run_bad_cmd("adc #Hi LaBe");

    return all_good;
}

}  // namespace CPU6502_TEST::interpreter_test::inner

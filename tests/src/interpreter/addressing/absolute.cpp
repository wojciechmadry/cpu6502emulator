#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"
#include "interpreter.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool ADDRESSING_ABSOLUTE_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    auto& all_reg = cpu.get_registers();

    utils::jump_to_2020(cpu);

    cpu6502::interpreter::Interpreter interp(cpu);
    const std::string label_name_good = "ProperAddress";

    // Label address: 0xFA06
    constexpr std::uint8_t LSB_good = 0x06;
    constexpr std::uint8_t MSB_good = 0xAA;
    constexpr std::uint32_t label_value_good = (MSB_good << 8) | LSB_good;

    interp.add_label(label_name_good, label_value_good);

    constexpr cpu6502::Byte absolute_val = 0xA5;

    auto run_test = [&](const std::string& command, std::uint8_t output, auto& reg) 
    {
        bool test_result = true;
        test_result &= reg.get() == 0;
        const auto addressing = interp.interprete(command);
        test_result &= addressing == cpu6502::interpreter::Addressing::Absolute;
        test_result &= reg.get() == output;
        reg.get() = 0;
        all_good &= test_result;
    };

    

    // Test correct command
    // Write '0x05' to zero page address '0x0006'
    mem[label_value_good] = absolute_val;

    // Test ADC $AA06
    run_test("adc $AA06", absolute_val, all_reg.ACU);
    
    // Test ADC $0AA06
    run_test("adc $0AA06", absolute_val, all_reg.ACU);

    // Test ADC ProperAddress
    run_test("adc ProperAddress", absolute_val, all_reg.ACU);

    // Test three command in row
    {
        cpu.reset();
        utils::jump_to_2020(cpu);
        auto& reg = cpu.get_registers();
        const std::string cmd1 = "adc $AA06";
        const std::string cmd2 = "adc $0AA06";
        const std::string cmd3 = "adc ProperAddress";
        interp.interprete(cmd1);
        interp.interprete(cmd2);
        interp.interprete(cmd3);
        all_good &= reg.ACU.get() == 254;
        reg.ACU.get() = 0;
        cpu.reset();
        utils::jump_to_2020(cpu);
    }
        
    
    {

        const auto addressing_0 = interp.interprete("jmp $1");
        all_good &= addressing_0 == cpu6502::interpreter::Addressing::Absolute;
        all_good &= 0x1 == all_reg.PC.get();

        const auto addressing_1 = interp.interprete("jmp $A04A");
        all_good &= addressing_1 == cpu6502::interpreter::Addressing::Absolute;
        all_good &= 0xA04A == all_reg.PC.get();

        
    }
    // Test bad command

    auto run_bad_cmd = [&](const std::string& command)
    {
        try
        {
            const auto addressing = interp.interprete(command);
            all_good &= addressing != cpu6502::interpreter::Addressing::Absolute;
        }
        catch(const std::exception&)
        {
            all_good &= true;
        }
        
    };

    // add AA06
    run_bad_cmd("add AA06");
    
    // add 0AA06
    run_bad_cmd("add 0AA06");

    // add $FFFF (out of range)
    run_bad_cmd("add $FFFF");

    // add label_name_bad
    run_bad_cmd("add label_name_bad");

    // Test CMP TODO: Implement test to Absolute CMP (It doesnt work)
    auto run_test_cmp = [&](const std::string& command, bool carry_flag, bool zero_flag) 
    {
        bool test_result = true;
        const auto addressing = interp.interprete(command);
        test_result &= addressing == cpu6502::interpreter::Addressing::Absolute;
        auto& PS = cpu.get_registers().PS;
        const auto carry = PS.get(cpu6502::registers::ProcessorStatus::Flags::CarryFlag);
        const auto zero = PS.get(cpu6502::registers::ProcessorStatus::Flags::ZeroFlag);
        all_good &= carry == carry_flag;
        all_good &= zero == zero_flag;
        all_good &= test_result;
    };

    utils::jump_to_2020(cpu);
    static constexpr cpu6502::Word my_memory_address = 666;
    interp.add_label("mymemory", my_memory_address);

    for(int memory_value = -25 ; memory_value <= 25 ; ++memory_value)
    {
        for(int acu_value = -25 ; acu_value <= 25 ; ++acu_value)
        {
            const bool carry_flag = acu_value >= memory_value; 
            const bool zero_flag = acu_value == memory_value;
            utils::load_to_acu(cpu, static_cast<cpu6502::Byte>(acu_value));
            mem[my_memory_address] = static_cast<cpu6502::Byte>(memory_value);
            std::string custom_command = "cmp mymemory";
            run_test_cmp(custom_command, carry_flag, zero_flag);
        }   
    }

    return all_good;
}

}  // namespace CPU6502_TEST::interpreter_test::inner

#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "processorstatus.hpp"
#include "required.hpp"
#include "utility/utility.hpp"
#include "interpreter.hpp"

#include <limits>
#include <string>

namespace CPU6502_TEST::interpreter_test::inner{

bool ADDRESSING_INDIRECT_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    auto& all_reg = cpu.get_registers();

    utils::jump_to_2020(cpu);


    cpu6502::interpreter::Interpreter interp(cpu);

    const std::string clear_carry = "clear_carry";
    constexpr std::uint8_t LSB_clear = 0xF0;
    constexpr std::uint8_t MSB_clear = 0xA4;
    constexpr std::uint32_t clear_carry_value = (MSB_clear << 8) | LSB_clear; // 0xA4F0

    const std::string set_carry = "set_carry";
    constexpr std::uint8_t LSB_set = 0xE4;
    constexpr std::uint8_t MSB_set = 0xD8;
    constexpr std::uint32_t set_carry_value = (MSB_set << 8) | LSB_set; // 0xD8E4

    interp.add_label(clear_carry, clear_carry_value);
    interp.add_label(set_carry, set_carry_value);

    constexpr cpu6502::Word clear_address = 0x01F0;
    constexpr cpu6502::Word set_address = 0x02F5;
    mem.write_word(clear_address, clear_carry_value);
    mem.write_word(set_address, set_carry_value);


    auto run_test = [&](const std::string& command, bool carry_value) 
    {
        const auto addressing = interp.interprete(command);
        all_good &= addressing == cpu6502::interpreter::Addressing::Indirect;
        all_good &= all_reg.PS.get(cpu6502::registers::ProcessorStatus::Flags::CarryFlag) == carry_value;
    };

    // Set PC to 0x2020 (prevent from infinite loop)
    auto reset_position = [&]()
    {
        mem[0x2020] = 0xFF;
        mem[0x2020 + 1] = 0xFF;
        all_reg.PC.set(0x2020);
        mem[clear_address] = static_cast<cpu6502::Byte>(cpu6502::opcode::CLC::Implied);
        mem[clear_address + 1] = 0xFF;
        mem[set_address] = static_cast<cpu6502::Byte>(cpu6502::opcode::SEC::Implied);
        mem[set_address + 1] = 0xFF;
        mem.write_word(clear_address, clear_carry_value);
        mem.write_word(set_address, set_carry_value);
    };

    // Test correct command
    
    reset_position();

    run_test("jmp ($D8E4)", true);
    
    reset_position();

    run_test("jmp ($D8E4)", true);

    run_test("jmp ($A4F0)", false);

    reset_position();

    run_test("jmp ($A4F0)", false);

    run_test("jmp ($D8E4)", true);

    reset_position();

    mem.initialise();

    // --- Label
    reset_position();

    run_test("jmp (clear_carry)", false);
    run_test("jmp (set_carry)", true);

    reset_position();

    run_test("jmp (set_carry)", true);

    run_test("jmp (clear_carry)", false);

    reset_position();

    run_test("jmp (clear_carry)", false);

    run_test("jmp (set_carry)", true);

    reset_position();

    
    // Test bad command

    auto run_bad_cmd = [&](const std::string& command)
    {
        try
        {
            const auto addressing = interp.interprete(command);
            all_good &= addressing != cpu6502::interpreter::Addressing::Indirect;
        }
        catch(const std::exception&)
        {
            all_good &= true;
        }
        
    };

    run_bad_cmd("jmp (FFFF)");
    run_bad_cmd("jmp (#FFFF)");
    run_bad_cmd("jmp ($FFFF)");
    run_bad_cmd("jmp ($$FFF)");
    run_bad_cmd("jmp (bad_label)");
    run_bad_cmd("jmp (bad_label");
    run_bad_cmd("jmp bad_label)");
    run_bad_cmd("jmp (set_carry");
    run_bad_cmd("jmp set_carry)");
    run_bad_cmd("jmp ($FFFF");
    run_bad_cmd("jmp $FFFF");
    run_bad_cmd("jmp $FFFF)");
    run_bad_cmd("jmp ($FFF");
    run_bad_cmd("jmp $FFA");
    run_bad_cmd("jmp $FFF)");
    run_bad_cmd("jmp (6)");
    run_bad_cmd("jmp (($F))");
    
    
    return all_good;
}

}  // namespace CPU6502_TEST::interpreter_test::inner

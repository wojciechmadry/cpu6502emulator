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

bool ADDRESSING_RELATIVE_TEST()
{
    bool all_good = true;
    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    auto& reg = cpu.get_registers();

    utils::jump_to_2020(cpu);

    cpu6502::interpreter::Interpreter interp(cpu);

    const std::string label_name_higher = "label_h";
    constexpr std::uint32_t  label_value_higher = 0x2040;
    const std::string label_name_lower = "label_l";
    constexpr std::uint32_t  label_value_lower = 0x2000;
    const std::string label_name_far_right = "label_right";
    constexpr std::uint32_t  label_value_far_right = 0x20A1;
    const std::string label_name_far_left = "label_left";
    constexpr std::uint32_t  label_value_far_left = 0x1FA2;

    interp.add_label(label_name_higher, label_value_higher);
    interp.add_label(label_name_lower, label_value_lower);
    interp.add_label(label_name_far_right, label_value_far_right);
    interp.add_label(label_name_far_left, label_value_far_left);

    auto run_test = [&](const std::string& command, cpu6502::Word new_PC) 
    {
        auto addressing = interp.interprete(command);
        all_good &= addressing == cpu6502::interpreter::Addressing::Relative;
        all_good &= reg.PC.get() == new_PC;
        utils::jump_to_2020(cpu);
        mem.initialise();
    };

    // How it works?
    // If branch -> add value to program counter (You need also add 2 because instruction increment program counter twice)
    // You can jump to label (You need define them before)

    // Test correct command

    // BCC - Branch if Carry Clear
    run_test("BCC label_h", label_value_higher);
    run_test("BCC label_l", label_value_lower);
    run_test("BCC label_right", label_value_far_right);
    run_test("BCC label_left", label_value_far_left);
    
    // BCS - Branch if Carry Set
    run_test("BCS label_h", reg.PC.get() + 2);
    run_test("BCS label_l", reg.PC.get() + 2);
    run_test("BCS label_right", reg.PC.get() + 2);
    run_test("BCS label_left", reg.PC.get() + 2);

    // Test few command in a row
    {
        utils::jump_to_2020(cpu);
        mem.initialise();
    
        interp.interprete("BCS label_h"); // PC == 0x2020 + 2
        mem.initialise();
        interp.interprete("BCC label_h"); // PC == label_value_higher
        mem.initialise();
        interp.interprete("BCS label_h"); // PC == label_value_higher + 2
        mem.initialise();
        interp.interprete("BCC label_right"); // PC == label_value_far_right
        mem.initialise();
        interp.interprete("BCC label_h"); // PC == label_value_higher
        mem.initialise();
        interp.interprete("BCC label_l"); // PC == label_value_lower
        mem.initialise();
        interp.interprete("BCC label_left"); // PC == label_value_far_left
        all_good &= reg.PC.get() == label_value_far_left;
        utils::jump_to_2020(cpu);
        mem.initialise();
    }
    
    run_test("BCC *+2", reg.PC.get() + 2);
    run_test("BCC *+4", reg.PC.get() + 4);
    run_test("BCC *+129", reg.PC.get() + 129);
    run_test("BCC *+10", reg.PC.get() + 10);
    mem.initialise();
    run_test("BCC *-4", reg.PC.get() - 4);
    run_test("BCC *-10", reg.PC.get() - 10);
    run_test("BCC *-126", reg.PC.get() - 126);
    mem.initialise();
    run_test("BCS *+2", reg.PC.get() + 2);
    run_test("BCS *+4", reg.PC.get() + 2);
    run_test("BCS *+129", reg.PC.get() + 2);
    run_test("BCS *+10", reg.PC.get() + 2);
    run_test("BCS *-4", reg.PC.get() + 2);
    run_test("BCS *-10", reg.PC.get() + 2);
    run_test("BCS *-126", reg.PC.get() + 2);

        // Test few command in a row
    {
        utils::jump_to_2020(cpu);
        mem.initialise();

        const auto PC_val = reg.PC.get();

        interp.interprete("BCC *+4"); // PC == 0x2020 + 4
        interp.interprete("BCC *+2"); // PC == 0x2020 + 6
        interp.interprete("BCC *+15"); // PC == 0x2020 + 6 + 15

        all_good &= (PC_val + 6 + 15) == reg.PC.get();

        utils::jump_to_2020(cpu);
        mem.initialise();
    }
    // Test bad command
    
    auto run_bad_cmd = [&](const std::string& command)
    {
        try
        {
            const auto addressing = interp.interprete(command);
            all_good &= addressing != cpu6502::interpreter::Addressing::Relative;
        }
        catch(const std::exception&)
        {
            all_good &= true;
        }
        
    };

    const std::string label_name_out_l= "label_out_l";
    const std::string label_name_out_r= "label_out_r";
    constexpr std::uint32_t  label_value_out_left = 0x2020 - 127;
    constexpr std::uint32_t  label_value_out_right = 0x2020 + 130;

    interp.add_label(label_name_out_l, label_value_out_left);
    interp.add_label(label_name_out_r, label_value_out_right);

    run_bad_cmd("BCC *+130");
    run_bad_cmd("BCC *-127");
    run_bad_cmd("BCC /-1");
    run_bad_cmd("BCC +-1");
    run_bad_cmd("BCC --1");
    run_bad_cmd("BCC -+1");
    run_bad_cmd("BCC **1");
    run_bad_cmd("BCC */1");
    run_bad_cmd("BCC bad_label");
    run_bad_cmd("BCC label_out_r");
    
    return all_good;
}

}  // namespace CPU6502_TEST::interpreter_test::inner

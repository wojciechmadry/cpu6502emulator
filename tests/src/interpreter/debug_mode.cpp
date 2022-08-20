#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"

#include <vector>
#include <string>
#include <random>

#include <fmt/core.h> // TODO: Delete this

namespace CPU6502_TEST::interpreter_test::inner{

bool DEBUG_MODE_TEST()
{
    std::vector<bool> all_tests;
    auto add_test = [&]()
    {
        all_tests.emplace_back(true);
    };

    auto test = [&](bool result_of_test)
    {
        if(!all_tests.empty())
        {
            all_tests.back() = all_tests.back() & result_of_test;
        }
    };

    // Pseudo random with standard seed
    std::vector<std::string> rnd_commands{"php", "nop", "lsr a", "ror a", "lda #225", "tax"};

    auto get_command = [&]()
    {
        return rnd_commands[static_cast<std::size_t>(rand())%rnd_commands.size()];
    };

    cpu6502::Memory mem(64 * 1024);
    cpu6502::CPU cpu(mem);
    cpu6502::interpreter::Interpreter interp(cpu);

    static constexpr auto X = static_cast<std::uint32_t>(12);
    static constexpr auto N = static_cast<std::uint32_t>(7);


    // Test 1 - Remember X states
    {
        interp.reset();
        add_test();
        test(!interp.get_current_state().has_value());
        test(interp.get_states_to_remember() == 0);

        interp.set_states_to_remember(X);
        test(!interp.get_current_state().has_value());
        test(interp.get_states_to_remember() == X);

        std::list<cpu6502::interpreter::Interpreter ::INTERPRETER_CLONE_TYPE> all_states;
        interp.interprete("jmp $600");

        for(std::uint32_t i = 0 ; i < X * X ; i += 4)
        {
            const auto cmd = get_command();
            all_states.emplace_back(interp.clone());
            interp.interprete(cmd);
            const auto& states = interp.get_debug_states();
            test(states.size() <= X);
            test(interp.get_states_to_remember() == X);
            test(--states.end() == interp.get_current_state());
        }

        const auto& states = interp.get_debug_states();
        auto rend_debug = states.rbegin();
        auto rend_all_states = all_states.rbegin();
        for ( ; rend_debug != states.rend() ; ++rend_debug, ++rend_all_states)
        {
            test(rend_debug->first == rend_all_states->first);
            test(*rend_debug->second.first == *rend_all_states->second.first);
            test(*rend_debug->second.second == *rend_all_states->second.second);
        }
    }

    // Test 2 - Go left for N states
    interp.reset();
    add_test();
    test(false);
    
    // Test 3 - Go right for N states
    interp.reset();
    //add_test();
    //test(false);
    
    // Test 4 - Go left for N states and execute new command
    interp.reset();
    //add_test();
    //test(false);


    for(auto test_result : all_tests)
    {
        if (test_result == false)
        {
            return false;
        }
    }
    return true;
}

}

#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"

#include <vector>
#include <string>
#include <random>
#include <cstdint>

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
    std::list<cpu6502::interpreter::Interpreter ::INTERPRETER_CLONE_TYPE> all_states;

    // Interpreter shouldnt remember any command after creation
    {
        add_test();
        interp.interprete(get_command());
        test(interp.get_states_to_remember() == 0);
        test(interp.get_debug_states().empty());
        test(!interp.get_current_state().has_value());
    }


    auto compare_iterator = [](const auto& lhs, const auto& rhs) -> bool
    {
        return lhs->first == rhs->first && *lhs->second.first == *rhs->second.first && *lhs->second.second == *rhs->second.second;
    };

    static constexpr auto X = static_cast<std::uint32_t>(12);
    static constexpr auto N = static_cast<std::uint32_t>(7);
    static_assert(X > N);
    static_assert(X > 0 && N > 0);

    // Test 1 - Remember X states
    {
        interp.reset();
        add_test();
        test(!interp.get_current_state().has_value());
        test(interp.get_states_to_remember() == 0);

        interp.set_states_to_remember(X);
        test(!interp.get_current_state().has_value());
        test(interp.get_states_to_remember() == X);

        interp.interprete("jmp $600");

        for(std::uint32_t i = 0 ; i < X * X ; i += 4)
        {
            const auto cmd = get_command();
            interp.interprete(cmd);
            all_states.emplace_back(interp.clone());
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
            compare_iterator(rend_debug, rend_all_states);
        }

        // Resize all_states to size of states
        while(all_states.size() != states.size())
        {
            all_states.pop_front();
        }
        rend_debug = states.rbegin();
        rend_all_states = all_states.rbegin();
        test(all_states.size() == states.size());
        for ( ; rend_debug != states.rend() ; ++rend_debug, ++rend_all_states)
        {
            compare_iterator(rend_debug, rend_all_states);
        }

    }

    // Test 2 - Go max left and right
    {
        const auto& states = interp.get_debug_states();
        add_test();
        test(states.size() == X);
        test(states.size() == all_states.size());

        // Go left
        test(compare_iterator(states.rbegin(), all_states.rbegin()));
        auto cur_state = interp.get_current_state();
        test(cur_state.has_value());
        if (cur_state.has_value())
        {
            test(compare_iterator(*cur_state, all_states.rbegin()));
        }

        for(std::size_t i = 0u ; i <= X * 2 ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoLeft);
        }
        cur_state = interp.get_current_state();
        test(cur_state.has_value());

        if(cur_state.has_value())
        {
            test(compare_iterator(*interp.get_current_state(), all_states.begin()));
        }

        //Go right
        for(std::size_t i = 0u ; i <= X * 2 ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoRight);
        }
        test(compare_iterator(*interp.get_current_state(), all_states.rbegin()));
    }

    // Test 3 - Go left for N states
    {
        const auto& states = interp.get_debug_states();
        add_test();
        test(states.size() == X);
        test(states.size() == all_states.size());
        test(compare_iterator(states.rbegin(), all_states.rbegin()));
        const auto cur_state = interp.get_current_state();
        test(cur_state.has_value());
        if (cur_state.has_value())
        {
            test(compare_iterator(*cur_state, all_states.rbegin()));
        }

        for(std::uint32_t i = 0u ; i < N ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoLeft);
            auto it_states = states.rbegin();
            auto it_all_states = all_states.rbegin();
            std::uint32_t count_to_i = 0u;
            for(auto j = static_cast<std::int32_t>(states.size() - 1) ; j >= 0 ; --j)
            {
                test(compare_iterator(it_states, it_all_states));
                ++it_states;
                ++it_all_states;
                ++count_to_i;
                const auto& current_state = interp.get_current_state();
                test(current_state.has_value());
                if (current_state.has_value() && count_to_i == i + 1u)
                {
                    test(compare_iterator(*current_state, it_all_states));
                }
            }
            
        }
    }
    
    // Test 4 - Go right for N states
    {
        const auto& states = interp.get_debug_states();
        add_test();
        test(states.size() == X);
        test(states.size() == all_states.size());
        test(compare_iterator(states.rbegin(), all_states.rbegin()));
        test(compare_iterator(states.begin(), all_states.begin()));

        // Go max left
        for(std::uint32_t i = 0 ; i <= X ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoLeft);
        }

        auto current_state = interp.get_current_state();
        test(current_state.has_value());
        if(current_state.has_value())
        {
            test(compare_iterator(*current_state, all_states.begin()));
        }


        for(std::uint32_t i = 0u ; i < N ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoRight);
            auto it_states = states.begin();
            auto it_all_states = all_states.begin();
            std::uint32_t count_to_i = 0u;
            for(auto j = 0u ; j < states.size() ; ++j)
            {
                test(compare_iterator(it_states, it_all_states));
                ++it_states;
                ++it_all_states;
                ++count_to_i;
                current_state = interp.get_current_state();
                test(current_state.has_value());
                if (current_state.has_value() && count_to_i == i + 1u)
                {
                    test(compare_iterator(*current_state, it_all_states));
                }
            }
        }

        // Go max right
        for(std::uint32_t i = 0 ; i <= X ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoRight);
        }
        current_state = interp.get_current_state();
        test(current_state.has_value());
        if (current_state.has_value())
        {
            test(compare_iterator(*current_state, all_states.rbegin()));
        }
    }
    
    // Test 5 - Go left for N states and execute new command
    {
        const auto& states = interp.get_debug_states();
        add_test();
        test(states.size() == X);
        test(states.size() == all_states.size());
        test(compare_iterator(states.rbegin(), all_states.rbegin()));
        test(compare_iterator(states.begin(), all_states.begin()));
        for(auto i = 0u ; i < N ; ++i)
        {
            interp.debug_mode_change_command(cpu6502::interpreter::utils::DebugModeNextCommand::GoLeft);
        }
        interp.interprete(get_command());
        test(states.size() < X);
        test(states.size() < all_states.size());
        test(states.size() > (X - N));
        test(!compare_iterator(states.rbegin(), all_states.rbegin()));
        auto it_states = states.begin();
        auto it_all_states = all_states.begin();

        for(std::size_t i = 0u ; i < states.size() - 1 ; ++i)
        {
            test(compare_iterator(it_states, it_all_states));
            ++it_states;
            ++it_all_states;
        }
    }

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

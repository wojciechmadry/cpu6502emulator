#include "interpreter_test.hpp"

#include "cpu.hpp"
#include "interpreter.hpp"

#include <vector>

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

    // Test 1 - Remember X states
    add_test();
    test(false);

    // Test 2 - Go left for N states
    add_test();
    test(false);
    
    // Test 3 - Go right for N states
    add_test();
    test(false);
    
    // Test 4 - Go left for N states and execute new command
    add_test();
    test(false);

    // Test 5 - Check get_current_state() function
    add_test();
    test(false);

    // Test 6 - Check debug_go_right() function
    add_test();
    test(false);

    // Test 7 - Check debug_go_left() function
    add_test();
    test(false);

    // Test 8 - Check clone() function
    add_test();
    test(false);

    // Test 9 - Check clone() function
    add_test();
    test(false);


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

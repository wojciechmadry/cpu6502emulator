#ifndef CPU_6502_TEST_CPU
#define CPU_6502_TEST_CPU

#include <string>
#include "test_logger.hpp"

namespace CPU6502_TEST
{
    template<typename Func>
    inline bool run_test(Func func, const std::string& test_name)
    {
        bool test_pass;
        try
        {
            test_pass = func();
        }
        catch(std::exception& e)
        {
            test_pass = false;
            log_messages("Test : ", test_name, " -> exception : ", e.what() , "\n");
        }
        log_test(test_name, test_pass);
        return test_pass;
    };
}

namespace CPU6502_TEST::inner
{

    bool RUN_CPU_TEST();
}
#endif
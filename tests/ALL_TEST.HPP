#ifndef CPU_6502_TEST_ALL_TEST
#define CPU_6502_TEST_ALL_TEST

#include "register_test.hpp"
#include "cpu_test.hpp"

namespace CPU6502_TEST
{
    void RUN_ALL_TEST(const size_t Times = 1) noexcept
    {
        babel::TIME::timer T;
        T.start();
        for(size_t i = 0 ; i < Times ; ++i)
        {
            bool tests = true;
            tests &= CPU6502_TEST::inner::RUN_REGISTER_TEST();
            tests &= CPU6502_TEST::inner::RUN_CPU_TEST();
            assert(tests);
        }
        auto Time = T.get_time();
        std::cout << "All test pass in : " << Time << " seconds.\n";
    }
}


#endif
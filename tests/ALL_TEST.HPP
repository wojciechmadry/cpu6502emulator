#ifndef CPU_6502_TEST_ALL_TEST
#define CPU_6502_TEST_ALL_TEST

#include "register_test.hpp"
#include "cpu_test.hpp"

namespace CPU6502_TEST
{
    void RUN_ALL_TEST(const size_t Times = 1) noexcept
    {
        for(size_t i = 0 ; i < Times ; ++i)
        {
            CPU6502_TEST::inner::RUN_REGISTER_TEST();
            CPU6502_TEST::inner::RUN_CPU_TEST();
        }
    }
}


#endif
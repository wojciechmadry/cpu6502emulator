#ifndef CPU_6502_TEST_ALL_TEST
#define CPU_6502_TEST_ALL_TEST

namespace CPU6502_TEST
{
    enum class TEST_RESULT
    {
        ALL_PASS,
        FAILED
    };

    TEST_RESULT RUN_ALL_TEST();
}


#endif

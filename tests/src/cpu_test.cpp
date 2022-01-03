#include "cpu_test.hpp"


#include "test_logger.hpp"
#include "instruction_test.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_CPU_TEST() noexcept
    {
        bool all_pass = true;
        bool temp;

        temp = LDA_TEST();
        all_pass &= temp;

        log_test("LDA", temp);

        temp = LDX_TEST();
        all_pass &= temp;

        log_test("LDX", temp);

        temp = LDY_TEST();
        all_pass &= temp;

        log_test("LDY", temp);

        temp = RTS_JSR_TEST();
        all_pass &= temp;

        log_test("RTS_JSR", temp);


        temp = JMP_TEST();
        all_pass &= temp;
        
        log_test("JMP", temp);

        temp = STA_TEST();
        all_pass &= temp;
        
        log_test("STA", temp);


        temp = STX_TEST();
        all_pass &= temp;
        
        log_test("STX", temp);


        temp = STY_TEST();
        all_pass &= temp;

        log_test("STY", temp);

        temp = STATUS_FLAG_CHANGES_TEST();
        all_pass &= temp;

        log_test("STATUS_FLAG_CHANGES", temp);


        temp = REGISTER_TRANSFER_TEST();
        all_pass &= temp;

        log_test("REGISTER_TRANSFER", temp);

        temp = STACK_OPERATIONS_TEST();
        all_pass &= temp;

        log_test("STACK_OPERATIONS", temp);

        temp = AND_TEST();
        all_pass &= temp;

        log_test("AND", temp);

        temp = BIT_TEST();
        all_pass &= temp;

        log_test("BIT", temp);

        temp = EOR_TEST();
        all_pass &= temp;

        log_test("EOR", temp);

        temp = ORA_TEST();
        all_pass &= temp;

        log_test("ORA", temp);

        temp = BRANCHES_TEST();
        all_pass &= temp;

        log_test("BRANCHES", temp);

        return all_pass;
    }
}
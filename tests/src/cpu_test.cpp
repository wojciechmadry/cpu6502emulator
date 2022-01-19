#include "cpu_test.hpp"


#include "test_logger.hpp"
#include "instruction_test.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_CPU_TEST()
    {
        bool all_pass = true;
        bool temp;

        try
        {
            temp = LDA_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("LDA", temp);

        try
        {
            temp = LDX_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("LDX", temp);

        try
        {
            temp = LDY_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("LDY", temp);

        try
        {
            temp = RTS_JSR_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("RTS_JSR", temp);

        try
        {
            temp = JMP_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;
        
        log_test("JMP", temp);

        try
        {
            temp = STA_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;
        
        log_test("STA", temp);

        try
        {
            temp = STX_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;
        log_test("STX", temp);

        try
        {
            temp = STY_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("STY", temp);

        try
        {
            temp = STATUS_FLAG_CHANGES_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("STATUS_FLAG_CHANGES", temp);

        try
        {
            temp = REGISTER_TRANSFER_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("REGISTER_TRANSFER", temp);

        try
        {
            temp = STACK_OPERATIONS_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("STACK_OPERATIONS", temp);

        try
        {
            temp = AND_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("AND", temp);

        try
        {
            temp = BIT_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("BIT", temp);

        try
        {
            temp = EOR_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("EOR", temp);

        try
        {
            temp = ORA_TEST();
        }
        catch(...)
        {
            temp = false;
        }

        all_pass &= temp;

        log_test("ORA", temp);

        try
        {
            temp = BRANCHES_TEST();
        }
        catch(...)
        {
            temp = false;
        }
        
        all_pass &= temp;

        log_test("BRANCHES", temp);

        return all_pass;
    }
}
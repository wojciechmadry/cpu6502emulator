#include "cpu_test.hpp"


#include "test_logger.hpp"
#include "instruction_test.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_CPU_TEST()
    {
        bool all_pass = true;

        auto run_test = []<typename Func>(Func func, const std::string& test_name)
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

        all_pass &= run_test(LDA_TEST, "LDA");

        all_pass &= run_test(LDX_TEST, "LDX");

        all_pass &= run_test(LDY_TEST, "LDY");

        all_pass &= run_test(RTS_JSR_TEST, "RTS_JSR");

        all_pass &= run_test(JMP_TEST, "JMP");
        
        all_pass &= run_test(STA_TEST, "STA");

        all_pass &= run_test(STX_TEST, "STX");

        all_pass &= run_test(STY_TEST, "STY");

        all_pass &= run_test(STATUS_FLAG_CHANGES_TEST, "STATUS_FLAG_CHANGES");

        all_pass &= run_test(REGISTER_TRANSFER_TEST, "REGISTER_TRANSFER");

        all_pass &= run_test(STACK_OPERATIONS_TEST, "STACK_OPERATIONS");

        all_pass &= run_test(AND_TEST, "AND");

        all_pass &= run_test(BIT_TEST, "BIT");

        all_pass &= run_test(EOR_TEST, "EOR");

        all_pass &= run_test(ORA_TEST, "ORA");

        all_pass &= run_test(BRANCHES_TEST, "BRANCHES");

        all_pass &= run_test(ADC_TEST, "ADC");

        all_pass &= run_test(SBC_TEST, "SBC");

        all_pass &= run_test(CMP_TEST, "CMP");

        all_pass &= run_test(CPX_TEST, "CPX");

        all_pass &= run_test(CPY_TEST, "CPY");

        return all_pass;
    }
}
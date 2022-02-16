#include "ALL_TEST.HPP"


#include "register_test.hpp"
#include "cpu_test.hpp"
#include "test_logger.hpp"
#include "time.hpp"
#include <string>

namespace CPU6502_TEST
{
    void RUN_ALL_TEST() noexcept
    {
        babel::TIME::timer T;
        T.start();
        bool ALL_GOOD = true;
        ALL_GOOD &= CPU6502_TEST::inner::RUN_REGISTER_TEST();
        ALL_GOOD &= CPU6502_TEST::inner::RUN_CPU_TEST();
        
        auto Time = T.get_time();

        if (ALL_GOOD)
        {
            log_message("All test ");
            log_message("pass", Colors::GREEN);
            log_message(" in :");
        }
        else
        {
            log_message("Tests ");
            log_message("fail", Colors::RED);
            log_message(" in : ");
        }    
        log_message(std::to_string(Time));
        log_message(" seconds.\n");
    }
}

#ifndef CPU_6502_TEST_CPU
#define CPU_6502_TEST_CPU
#include "InstructionSetTest/LDA_TEST.HPP"
#include "InstructionSetTest/LDX_TEST.HPP"
#include "InstructionSetTest/LDY_TEST.HPP"
#include "InstructionSetTest/STA_TEST.HPP"
#include "InstructionSetTest/STX_TEST.HPP"
#include "InstructionSetTest/STY_TEST.HPP"
#include "InstructionSetTest/RTS_JSR_TEST.HPP"
#include "InstructionSetTest/JMP_TEST.HPP"
#include "InstructionSetTest/StatusFlagChanges.HPP"
#include "InstructionSetTest/REGISTER_TRANSFER.HPP"
#include "InstructionSetTest/STACK_OPERATIONS.HPP"
#include "InstructionSetTest/AND.HPP"
#include "InstructionSetTest/BIT.HPP"
#include "InstructionSetTest/EOR.HPP"
#include "InstructionSetTest/ORA.HPP"
#include "InstructionSetTest/BRANCHES_TEST.HPP"

#include "time.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_CPU_TEST() noexcept
    {
        bool all_pass = true;
        bool temp;

        temp = LDA_TEST();
        all_pass &= temp;

        if(!temp)
            std::cout << "LDA_TEST not pass ! \n";

        temp = LDX_TEST();
        all_pass &= temp;

        if(!temp)
            std::cout << "LDX_TEST not pass ! \n";

        temp = LDY_TEST();
        all_pass &= temp;

        if(!temp)
            std::cout << "LDY_TEST not pass ! \n";

        temp = RTS_JSR_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "RTS_JSR not pass ! \n";

        temp = JMP_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "JMP_TEST not pass ! \n";

        temp = STA_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "STA_TEST not pass ! \n";

        temp = STX_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "STX_TEST not pass ! \n";

        temp = STY_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "STY_TEST not pass ! \n";

        temp = STATUS_FLAG_CHANGES_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "STATUS_FLAG_CHANGES_TEST not pass ! \n";

        temp = REGISTER_TRANSFER_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "REGISTER_TRANSFER_TEST not pass ! \n";

        temp = STACK_OPERATIONS_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "STACK_OPERATIONS_TEST not pass ! \n";

        temp = AND_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "AND_TEST not pass ! \n";

        temp = BIT_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "BIT_TEST not pass ! \n";

        temp = EOR_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "EOR_TEST not pass ! \n";

        temp = ORA_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "ORA_TEST not pass ! \n";

        temp = BRANCHES_TEST();
        all_pass &= temp;
        if(!temp)
            std::cout << "BRANCHES_TEST not pass ! \n";

        return all_pass;
    }
}
#endif
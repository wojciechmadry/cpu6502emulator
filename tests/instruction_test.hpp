#ifndef INSTRUCTION_TEST_HPP
#define INSTRUCTION_TEST_HPP

namespace CPU6502_TEST::inner{
    
    bool AND_TEST() noexcept;
    
    bool BIT_TEST() noexcept;

    bool BRANCHES_TEST() noexcept;

    bool EOR_TEST() noexcept;

    bool JMP_TEST() noexcept;

    bool LDA_TEST() noexcept;

    bool LDX_TEST() noexcept;

    bool LDY_TEST() noexcept;

    bool ORA_TEST() noexcept;

    bool REGISTER_TRANSFER_TEST() noexcept;

    bool RTS_JSR_TEST() noexcept;

    bool STA_TEST() noexcept;

    bool STACK_OPERATIONS_TEST() noexcept;

    bool STATUS_FLAG_CHANGES_TEST() noexcept;

    bool STX_TEST() noexcept;

    bool STY_TEST() noexcept;

}

#endif  // INSTRUCTION_TEST_HPP
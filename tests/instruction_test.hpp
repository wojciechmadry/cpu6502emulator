#ifndef INSTRUCTION_TEST_HPP
#define INSTRUCTION_TEST_HPP

namespace CPU6502_TEST::inner{
    
    bool AND_TEST() ;
    
    bool BIT_TEST() ;

    bool BRANCHES_TEST() ;

    bool EOR_TEST() ;

    bool JMP_TEST() ;

    bool LDA_TEST() ;

    bool LDX_TEST() ;

    bool LDY_TEST() ;

    bool ORA_TEST() ;

    bool REGISTER_TRANSFER_TEST() ;

    bool RTS_JSR_TEST() ;

    bool STA_TEST() ;

    bool STACK_OPERATIONS_TEST() ;

    bool STATUS_FLAG_CHANGES_TEST() ;

    bool STX_TEST();

    bool STY_TEST();

    bool ADC_TEST();

    bool SBC_TEST();

    bool CMP_TEST();

    bool CPX_TEST();
    
    bool CPY_TEST();
}

#endif  // INSTRUCTION_TEST_HPP
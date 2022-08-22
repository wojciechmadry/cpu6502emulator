#include "interpreter_test.hpp"
#include "utility/test_utils.hpp"

namespace CPU6502_TEST::interpreter_test
{
    bool RUN_INTERPRETER_TEST()
    {
        bool all_pass = true;

        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_IMMEDIATE_TEST, "INTERPRETER_ADDRESSING_IMMEDIATE");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ZERO_PAGE_TEST, "INTERPRETER_ADDRESSING_ZERO_PAGE");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ZERO_PAGE_X_TEST, "INTERPRETER_ADDRESSING_ZERO_PAGE_X");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ZERO_PAGE_Y_TEST, "INTERPRETER_ADDRESSING_ZERO_PAGE_Y");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ABSOLUTE_TEST, "INTERPRETER_ADDRESSING_ABSOLUTE");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ABSOLUTE_X_TEST, "INTERPRETER_ADDRESSING_ABSOLUTE_X");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ABSOLUTE_Y_TEST, "INTERPRETER_ADDRESSING_ABSOLUTE_Y");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_IMPLICIT_TEST, "INTERPRETER_ADDRESSING_IMPLICIT");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_ACCUMULATOR_TEST, "INTERPRETER_ADDRESSING_ACCUMULATOR");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_RELATIVE_TEST, "INTERPRETER_ADDRESSING_RELATIVE");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_INDIRECT_TEST, "INTERPRETER_ADDRESSING_INDIRECT");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_INDIRECT_X_TEST, "INTERPRETER_ADDRESSING_INDIRECT_X");

        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::ADDRESSING_INDIRECT_Y_TEST, "INTERPRETER_ADDRESSING_INDIRECT_Y");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::LABEL_AND_COMMENT_TEST, "INTERPRETER_CREATE_LABEL_AND_COMMENTS");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::FIBONACCI_TEST, "INTERPRETER_FIBONACCI_EXAMPLE_TEST");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::FACTORIAL_TEST, "INTERPRETER_FACTORIAL_EXAMPLE_TEST");
        
        all_pass &= utils::run_test(CPU6502_TEST::interpreter_test::inner::DEBUG_MODE_TEST, "INTERPRETER_DEBUG_MODE_TEST");
        
        return all_pass;
    }
}
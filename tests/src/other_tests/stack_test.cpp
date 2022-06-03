#include "cpu_test.hpp"

#include "cpu.hpp"
#include "utility/utility.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_STACK_TEST()
    {
        bool all_good = true;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        constexpr auto STACK_BEGIN = cpu6502::CPU::STACK_BEGIN;
        constexpr auto STACK_END = cpu6502::CPU::STACK_END;

        utils::jump_to_2020(cpu);

        all_good &= STACK_BEGIN == 0x0100;
        all_good &= STACK_END == 0x01FF;

        cpu6502::u32 element_in_stack = 0u;
        cpu6502::u32 last_value_on_stack = 1u;
        auto& stack_pointer = cpu.get_registers().SP;

        all_good &= stack_pointer.get() == 0xFF;

        // Push 255 elements into stack
        for(cpu6502::u32 begin = STACK_BEGIN ; begin < STACK_END ; ++begin)
        {
            utils::push_to_stack(cpu, static_cast<cpu6502::Byte>(last_value_on_stack));
            ++element_in_stack;
            all_good &= mem[stack_pointer.get() + STACK_BEGIN + 1] == last_value_on_stack;
            ++last_value_on_stack;
        }

        all_good &= element_in_stack == 0xFF;
        // Pop 255 elements from stack
        for(cpu6502::u32 begin = STACK_BEGIN ; begin < STACK_END ; ++begin)
        {
            --last_value_on_stack;
            const auto pop = utils::pop_from_stack(cpu);
            --element_in_stack;
            all_good &= last_value_on_stack == pop;
            
        }

        all_good &= element_in_stack == 0x00;
        
        return all_good;
    }
}
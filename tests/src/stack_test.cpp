#include "stack_test.hpp"

#include "cpu.hpp"

#include "test_logger.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_STACK_TEST()
    {
        bool all_good = true;
       // using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        cpu6502::Byte opcode;

        constexpr auto STACK_BEGIN = cpu6502::CPU::STACK_BEGIN;
        constexpr auto STACK_END = cpu6502::CPU::STACK_END;

        auto PC = cpu.get_registers().PC.get();

        auto JUMP_TO_2020 = [&]()
        {
            PC = cpu.get_registers().PC.get();
            mem[PC++] = static_cast<cpu6502::Byte>(cpu6502::opcode::JMP::Absolute);
            mem[PC++] = 0x20;
            mem[PC++] = 0x20;
            cpu.execute(3);
            cpu.get_registers().PS.put_byte(0x00);
            PC = cpu.get_registers().PC.get();
            all_good &= PC == 0x2020;
        };  
      
        auto load_to_acu = [&]<typename INT, typename OPCODE = cpu6502::opcode::LDA>(INT value, OPCODE op = cpu6502::opcode::LDA::Immediate)
        {
            const auto set_ACU_opcode = static_cast<decltype(opcode)>(op); // 2 cycles
            PC = cpu.get_registers().PC.get();
            mem[PC++] = set_ACU_opcode;
            const auto value_casted = static_cast<cpu6502::Byte>(value);
            mem[PC++] = value_casted;
            cpu.execute(2);
        };

        auto push_to_stack = [&](const cpu6502::Byte val)
        {
            load_to_acu(val);
           
            all_good &= cpu.get_registers().ACU.get() == val;
            const auto sp_before = cpu.get_registers().SP.get();

            mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::PHA::Implied); // 3 cycles
            cpu.execute(3);

            const auto sp_after = cpu.get_registers().SP.get();
            all_good &= sp_after == (sp_before - 1);


        };

        auto pop_from_stack = [&]() -> cpu6502::Byte
        {
            const auto sp_before = cpu.get_registers().SP.get();

            const auto last_val_on_stack = mem[cpu.get_registers().SP.get() + 1 + STACK_BEGIN];
            
            mem[PC++] = static_cast<decltype(opcode)>(cpu6502::opcode::PLA::Implied); // 4 cycles
            cpu.execute(4);
        
            const auto sp_after = cpu.get_registers().SP.get();

            const auto ACU = cpu.get_registers().ACU.get();

            all_good &= ACU == last_val_on_stack;
            all_good &= sp_after == (sp_before + 1);

            return ACU;
        };

        JUMP_TO_2020();

        all_good &= STACK_BEGIN == 0x0100;
        all_good &= STACK_END == 0x01FF;

        cpu6502::u32 element_in_stack = 0u;
        cpu6502::u32 last_value_on_stack = 1u;
        auto& stack_pointer = cpu.get_registers().SP;

        all_good &= stack_pointer.get() == 0xFF;

        // Push 255 elements into stack
        for(cpu6502::u32 begin = STACK_BEGIN ; begin < STACK_END ; ++begin)
        {
            push_to_stack(static_cast<cpu6502::Byte>(last_value_on_stack));
            ++element_in_stack;
            all_good &= mem[stack_pointer.get() + STACK_BEGIN + 1] == last_value_on_stack;
            ++last_value_on_stack;
        }

        all_good &= element_in_stack == 0xFF;

        // Pop 255 elements from stack
        for(cpu6502::u32 begin = STACK_BEGIN ; begin < STACK_END ; ++begin)
        {
            --last_value_on_stack;
            const auto pop = pop_from_stack();
            --element_in_stack;
            all_good &= last_value_on_stack == pop;
            
        }

        all_good &= element_in_stack == 0x00;
        
        return all_good;
    }
}
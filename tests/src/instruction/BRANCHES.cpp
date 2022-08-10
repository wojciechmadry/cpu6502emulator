#include "instruction_test.hpp"

#include "cpu.hpp"

#include "utility/utility.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool BRANCHES_TEST()
    {
        bool all_good = true;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);
        auto cast = []<typename T>(const T Opcode) -> cpu6502::Byte
        {
            return static_cast<cpu6502::Byte>(Opcode);
        };

        auto set_flag = [&](PSFlags flags, bool value) mutable
        {
            cpu.get_registers().PS.set(flags, value);
        };

        utils::jump_to_2020(cpu);
        
        auto PC = cpu.get_registers().PC.get();

        // BCC
        mem[PC++] = cast(cpu6502::opcode::BCC::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::CarryFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BCC::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        // BCS

        mem[PC++] = cast(cpu6502::opcode::BCS::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::CarryFlag, false);

        mem[PC++] = cast(cpu6502::opcode::BCS::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        // BEQ
        mem[PC++] = cast(cpu6502::opcode::BEQ::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::ZeroFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BEQ::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();

        // BMI
        mem[PC++] = cast(cpu6502::opcode::BMI::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::NegativeFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BMI::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();

        //BNE
        set_flag(PSFlags::ZeroFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BNE::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::ZeroFlag, false);

        mem[PC++] = cast(cpu6502::opcode::BNE::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();

        //BPL
        set_flag(PSFlags::NegativeFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BPL::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::NegativeFlag, false);

        mem[PC++] = cast(cpu6502::opcode::BPL::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();


        // BVC
        set_flag(PSFlags::OverflowFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BVC::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::OverflowFlag, false);

        mem[PC++] = cast(cpu6502::opcode::BVC::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;
        PC = cpu.get_registers().PC.get();

        // BVS
        set_flag(PSFlags::OverflowFlag, false);

        mem[PC++] = cast(cpu6502::opcode::BVS::Relative); // 2 cycles
        mem[PC++] = 8;
        cpu.execute(2);
        all_good &= cpu.get_registers().PC.get() == PC;
        PC = cpu.get_registers().PC.get();

        set_flag(PSFlags::OverflowFlag, true);

        mem[PC++] = cast(cpu6502::opcode::BVS::Relative); // 3 cycles
        mem[PC++] = 8;
        cpu.execute(3);
        all_good &= cpu.get_registers().PC.get() == PC + 8;

        return all_good;
    }
}

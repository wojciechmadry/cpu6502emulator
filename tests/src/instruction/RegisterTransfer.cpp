#include "instruction_test.hpp"

#include "utility/test_utils.hpp"
#include "cpu.hpp"
#include "cpu/InstructionSet/opcode.hpp"

namespace CPU6502_TEST::inner{
    bool REGISTER_TRANSFER_TEST()
    {
        bool all_good = true;
        cpu6502::Memory mem(64 * 1024);
        cpu6502::CPU cpu(mem);

        auto cast = []<typename T>(T opcode) -> cpu6502::Byte
        {
           return static_cast<cpu6502::Byte>(opcode);
        };

        utils::jump_to_2020(cpu);
        auto PC = cpu.get_registers().PC.get();

        //ASSERT TAX
        mem[PC++] = cast(cpu6502::opcode::LDA::Immediate); //2 cycles
        mem[PC++] = 84;
        cpu.execute(2);
        all_good &= (cpu.get_registers().ACU.get() == 84);
        mem[PC++] = cast(cpu6502::opcode::TAX::Implied); // 2 cycles
        cpu.execute(2);
        all_good &= (cpu.get_registers().ACU.get() == cpu.get_registers().IRX.get());
        //END ASSERT TAX

        //ASSERT TAY
        mem[PC++] = cast(cpu6502::opcode::TAY::Implied); // 2 cycles
        cpu.execute(2);
        all_good &= (cpu.get_registers().ACU.get() == cpu.get_registers().IRY.get());
        //END TAY

        //ASSERT TXA
        mem[PC++] = cast(cpu6502::opcode::LDA::Immediate); // 2 cycles
        mem[PC++] = 0x12;
        mem[PC++] = cast(cpu6502::opcode::TXA::Implied); // 2 cycles;
        cpu.execute(4);
        all_good &= (cpu.get_registers().ACU.get() == cpu.get_registers().IRX.get() && cpu.get_registers().IRX.get() == 84);
        //END ASSERT TXA

        //ASSERT TYA
        mem[PC++] = cast(cpu6502::opcode::LDA::Immediate); // 2 cycles
        mem[PC++] = 0x12;
        mem[PC++] = cast(cpu6502::opcode::TYA::Implied); // 2 cycles;
        cpu.execute(4);
        all_good &= (cpu.get_registers().ACU.get() == cpu.get_registers().IRY.get() && cpu.get_registers().IRY.get() == 84);
        //END ASSERT TYA

        return all_good;
    }
}
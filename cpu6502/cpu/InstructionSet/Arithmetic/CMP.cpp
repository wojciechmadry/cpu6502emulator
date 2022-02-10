#include "cpu.hpp"

namespace cpu6502{
    
    void set_flags(cpu6502::Registers& reg, const bool carry, const bool zero, const bool negative) noexcept
    {
        reg.PS.set(CPU::PSFlags::CarryFlag, carry);
        reg.PS.set(CPU::PSFlags::ZeroFlag, zero);
        reg.PS.set(CPU::PSFlags::NegativeFlag, negative);
    }

    void cmp_operation(CPU& cpu, const Byte fetched) noexcept
    {
        auto& reg = cpu.get_registers();
        const auto acu = reg.ACU.get();
        const auto result = static_cast<Byte>(acu - fetched);

        set_flags(reg, acu >= fetched, acu == fetched, static_cast<bool>(result & 0x80));
        reg.ACU.set(result);
    }

    void CPU::CMPimmediate(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Immediate>(Cycles);
        cmp_operation(*this, fetched);
    }

    void CPU::CMPzeropage(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPage>(Cycles);
        cmp_operation(*this, fetched);
    }

    void CPU::CMPzeropagex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::ZeroPageX>(Cycles);
        cmp_operation(*this, fetched);;    
    }

    void CPU::CMPabsolute(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::Absolute>(Cycles);
        cmp_operation(*this, fetched);
    }


    void CPU::CMPabsolutex(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteX>(Cycles);
        cmp_operation(*this, fetched);  
    }


    void CPU::CMPabsolutey(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::AbsoluteY>(Cycles);
        cmp_operation(*this, fetched);
    }


    void CPU::CMPindirectx(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectX>(Cycles);
        cmp_operation(*this, fetched);   
    }


    void CPU::CMPindirecty(u32& Cycles) noexcept
    {
        const auto fetched = fetch<AddressingMode::IndirectY>(Cycles);
        cmp_operation(*this, fetched);      
    }
    
}
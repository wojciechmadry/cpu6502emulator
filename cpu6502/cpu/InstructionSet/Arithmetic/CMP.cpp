#include "cpu.hpp"

namespace cpu6502{

    void cmp_operation(CPU& cpu, const Byte fetched) noexcept
    {
        auto& reg = cpu.get_registers();
        const auto acu = reg.ACU.get();
        const auto result = static_cast<Byte>(acu - fetched);

        reg.PS.set(CPU::PSFlags::CarryFlag, acu >= fetched);
        reg.PS.set(CPU::PSFlags::ZeroFlag, acu == fetched);
        reg.PS.set(CPU::PSFlags::NegativeFlag, static_cast<bool>(result & 0x80));
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
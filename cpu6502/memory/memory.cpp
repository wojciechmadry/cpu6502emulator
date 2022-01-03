#include "memory.hpp"

#include "exceptions/cpu_except.hpp"

namespace cpu6502{

    void Memory::throw_out_of_range(const u64 Address) const
    {
        std::string msg = std::string("Address : ") + std::to_string(Address) + " is out of memory range.";
        throw std::out_of_range(msg);
    }

    void Memory::initialise() noexcept {
        for (auto &MemoryCell : m_memory)
        {
            MemoryCell = 0;    
        }
    }


    [[nodiscard]] Word Memory::read_word(const u64 Address) const
    {
        if(Address >= m_memory.size())
        {
            throw_out_of_range(Address);
        }
        else if (Address + 1u >= m_memory.size())
        {
            throw_out_of_range(Address + 1u);
        }

        Word Data = m_memory[Address];
        Data = static_cast<Word>(Data | (m_memory[Address + 1] << 8));
        return Data;
    }

    void Memory::write_word(const Word Data, const u64 Address)
    {
        if(Address >= m_memory.size())
        {
            throw_out_of_range(Address);
        }
        else if (Address + 1u >= m_memory.size())
        {
            throw_out_of_range(Address + 1u);
        }

        m_memory[Address] = static_cast<Byte>(Data & 0x00FF);
        m_memory[Address+1] = static_cast<Byte>(Data >> 8);
    }

    [[nodiscard]] Byte Memory::operator[](const u64 Address) const
    {
        if (Address >= m_memory.size())
        {
            throw_out_of_range(Address);
        }

        return m_memory[Address];
    }

    [[nodiscard]] Byte& Memory::operator[](const u64 Address)
    {
        if (Address >= m_memory.size())
        {
            throw_out_of_range(Address);
        }

        return m_memory[Address];
    }
}
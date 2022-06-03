#include "utility.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_indirect_y(std::string_view address, std::string_view value_in_bracket)
{
    if(value_in_bracket.empty())
    {
        return {};
    }

    for(std::size_t i = 0 ; address[i] != '(' ; ++i)
    {
        if(address[i] != ' ')
        {
            return {};
        }
    }

    for(std::size_t i = address.size() - 1 ; address[i] != ')'; --i)
    {
        if(address[i] != ' ')
        {
            if (std::toupper(address[i]) != 'Y')
            {
                return {};
            }
            else
            {
                 for(std::int64_t j = static_cast<std::int64_t>(i) - 1 ; j >= 0; --j)
                {
                    if(address[static_cast<std::size_t>(j)] != ' ')
                    {
                        if(address[static_cast<std::size_t>(j)] != ',')
                        {
                            return {};
                        }
                        break;
                    }
                }
            }
            break;
        }
    }

    std::string value;
    for(auto ch : value_in_bracket)
    {
        if(ch != ' ')
        {
            value += ch;
        }
    }
    if(value[0] == '$')
    {
        value = std::string{value.begin() + 1, value.end()};
        bool is_num = true;
        for(auto ch : value)
        {
            if(!is_number(ch, VALUE_TYPE::hex))
            {
                is_num = false;
                break;
            }
        }
        if(is_num)
        {
            return AddressInfo::create_address(Addressing::IndirectY, AVL_type::address, value);
        }
    }
    else if(is_propper_label(value))
    {
        return AddressInfo::create_address(Addressing::IndirectY, AVL_type::label, value);
    }
    
    return {};
}

}
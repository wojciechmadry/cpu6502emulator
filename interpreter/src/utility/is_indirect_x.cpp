#include "utility.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_indirect_x(std::string_view address, std::string_view value_in_bracket)
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
            return {};
        }
    }


    std::string value, type;
    std::string* access = &value;
    

    for(std::size_t i = 0 ; i < value_in_bracket.size() ; ++i)
    {
        if(value_in_bracket[i] != ' ')
        {
            if (value_in_bracket[i] == ',')
            {
                if(access == &type)
                {
                    return {};
                }
                access = &type;
            }
            else
            {
                (*access) += value_in_bracket[i];
            }
        }
    }

    if(!(type.size() == 1 && std::toupper(type[0]) == 'X'))
    {   
        return {};
    }

    
    if(value[0] == '$')
    {
        value = std::string(value.begin() + 1, value.end());
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
            return AddressInfo::create_address(Addressing::IndirectX, AVL_type::address, value);
        }
    }
    else if(is_propper_label(value))
    {
        return AddressInfo::create_address(Addressing::IndirectX, AVL_type::label, value);
    }
    
    return {};
}

}
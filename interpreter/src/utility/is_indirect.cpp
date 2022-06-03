#include "utility.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_indirect(std::string_view address, std::string_view value_in_bracket)
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


    auto bracket_val = std::string{value_in_bracket};
    remove_space_front_end(bracket_val);
    
    if(bracket_val[0] == '$')
    {
        auto value = std::string(bracket_val.begin() + 1, bracket_val.end());
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
            return AddressInfo::create_address(Addressing::Indirect, AVL_type::address, value);
        }
    }
    else if(is_propper_label(bracket_val))
    {
        return AddressInfo::create_address(Addressing::Indirect, AVL_type::label, bracket_val);
    }
    
    return {};
}

}
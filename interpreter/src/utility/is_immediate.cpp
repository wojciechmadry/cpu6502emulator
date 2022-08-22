#include "interp_utils.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_immediate(std::string_view address, std::size_t hash_position)
{
    if(hash_position != std::string::npos)
    {
        auto begin = address.begin() + hash_position + 1u;
        std::string value {""};
        std::string label {""};
        bool LO = false, HI = false;
        VALUE_TYPE value_type = VALUE_TYPE::decimal;
        if(begin != address.end())
        {
            if(*begin == '%')
            {
                value_type = VALUE_TYPE::binary;
                ++begin;
            }
            else if(*begin == '$')
            {
                value_type = VALUE_TYPE::hex;
                ++begin;
            }

            if(is_number(*begin, value_type))
            {
                while(begin != address.end())
                {
                    value += *begin;
                    ++begin;
                }
                for(const auto ch : value)
                {
                    if (!is_number(ch, value_type))
                    {
                        value = "";
                        break;
                    }
                }
            }
            else
            {
                if (std::toupper(*begin) == 'H')
                {
                    ++begin;
                    if (begin != address.end() && std::toupper(*begin) == 'I')
                    {
                        HI = true;
                        ++begin;
                    }
                }
                else if (std::toupper(*begin) == 'L')
                {
                    ++begin;
                    if (begin != address.end() && std::toupper(*begin) == 'O')
                    {
                        LO = true;
                        ++begin;
                    }
                }

                if(LO || HI)
                while(begin != address.end())
                {
                    if(*begin != ' ')
                    {
                        label += static_cast<char>(std::toupper(*begin));
                    }
                    ++begin;
                }
            }
            
        }


        if(!value.empty())
        {
            return AddressInfo::create_address(Addressing::Immediate, AVL_type::value, value, value_type);
        }
        else if(!label.empty())
        {
            auto addr = AddressInfo::create_address(Addressing::Immediate, AVL_type::label, label);
            if(LO)
            {
                addr.set_additional_info(ADDITIONAL_info::LO);
            }
            else if(HI)
            {
                addr.set_additional_info(ADDITIONAL_info::HI);
            }
            return addr;
        }
    }
    return {};
}

}
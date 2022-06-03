#include "utility.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_relative(std::string_view address)
{
    if(is_propper_label(address))
    {
        std::string addr {address};
        remove_space_front_end(addr);
        return AddressInfo::create_address(Addressing::Relative, AVL_type::label, std::move(addr));
    }

    const auto found_star = address.find('*');
    std::size_t num_start_in;
    if(found_star != std::string::npos)
    {
        char plus_or_minus = '_';
        for(std::size_t i = found_star + 1u; i < address.size() ; ++i)
        {
            if(address[i] == '+' || address[i] == '-')
            {
                plus_or_minus = address[i];
                num_start_in = i + 1u;
                break;
            }
            else if(address[i] != ' ')
            {
                break;
            }
        }

        if(plus_or_minus != '_')
        {
            std::string val {""};
            for(;num_start_in < address.size(); ++ num_start_in)
            {
                if(address[num_start_in] >= '0' && address[num_start_in] <= '9')
                {
                    val += address[num_start_in];
                }
                else if (address[num_start_in] != ' ')
                {
                    val.clear();
                    break;
                }
            }

            if(!val.empty())
            {
                return AddressInfo::create_address(Addressing::Relative, AVL_type::value, std::move(std::string{plus_or_minus} + val));
            }
        }
    }
    return {};
}

}
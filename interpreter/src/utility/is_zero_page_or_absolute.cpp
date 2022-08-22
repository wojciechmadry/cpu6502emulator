#include "interp_utils.hpp"
#include <limits>

namespace cpu6502::interpreter::utils{

std::pair<std::optional<AddressInfo>, std::optional<AddressInfo>> is_zero_page_or_absolute(std::string_view address, std::size_t dolar_position)
{
    if(dolar_position != std::string::npos)
    {
        std::string val {""};
        auto begin = address.begin() + dolar_position + 1;
        for(;begin != address.end();++begin)
        {
            if(is_number(*begin, VALUE_TYPE::hex))
            {
                val += *begin;
            }
            else
            {
                val.clear();
                break;
            }
        }
        if(!val.empty())
        {
            std::uint32_t iaddr = 0;
            try
            {
                iaddr = static_cast<std::uint32_t>(std::stoul(val, 0, 16));
            }
            catch(const std::exception&)
            {
                iaddr = std::numeric_limits<std::uint32_t>::max();
            }

            if(iaddr != std::numeric_limits<std::uint32_t>::max())
            {
                return {AddressInfo::create_address(Addressing::ZeroPage, AVL_type::address, val), AddressInfo::create_address(Addressing::Absolute, AVL_type::address, val)};
            }
        }
    }
    else if(is_propper_label(address))
    {
        std::string addr {address};
        remove_space_front_end(addr);
        return {AddressInfo::create_address(Addressing::ZeroPage, AVL_type::label, addr), AddressInfo::create_address(Addressing::Absolute, AVL_type::label, addr)};
    }
    return {};
}

}
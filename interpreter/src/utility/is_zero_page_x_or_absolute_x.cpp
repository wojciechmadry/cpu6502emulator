#include "interp_utils.hpp"
#include <limits>

namespace cpu6502::interpreter::utils{

std::pair<std::optional<AddressInfo>, std::optional<AddressInfo>> is_zero_page_x_or_absolute_x(std::string_view address, std::size_t dolar_position, std::size_t comma_position)
{
    if (address.empty())
    {
        return {};
    }
    // Check if address don't have bracket '(' ')'
    for(std::size_t i = 0u ; i < address.size() ; ++i)
    {
        if(address[i] == '(' || address[i] == ')')
        {
            return {};
        }
    }

    bool is_x_addressing = false;
    const auto X_found = address.find('X');
    if (X_found != std::string::npos)
    {
        is_x_addressing = true;
    }
    else if(address.find('x') != std::string::npos)
    {
        is_x_addressing = true;
    }

    if (comma_position == std::string::npos)
    {
        return {};
    }
    else
    {
        bool found_x = false;
        for(std::size_t i = comma_position + 1 ; i < address.size() ; ++i)
        {
            if(std::toupper(address[i]) == 'X')
            {
                found_x = true;
                break;
            }
            else if (address[i] != ' ')
            {
                break;
            }
        }
        if(!found_x)
        {
            return {};
        }
    }

    const auto propably_label = address.substr(0, comma_position); // Can be label name

    if(dolar_position != std::string::npos && is_x_addressing)
    {
        std::string val {""};
        auto begin = address.begin() + dolar_position + 1;
        const auto end = address.begin() + comma_position;
        for(;begin != end;++begin)
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
                return {AddressInfo::create_address(Addressing::ZeroPageX, AVL_type::address, val), AddressInfo::create_address(Addressing::AbsoluteX, AVL_type::address, val)};
            }
        }
    }
    else if(is_propper_label(propably_label) && is_x_addressing)
    {
        std::string addr {propably_label};
        remove_space_front_end(addr);
        return {AddressInfo::create_address(Addressing::ZeroPageX, AVL_type::label, addr), AddressInfo::create_address(Addressing::AbsoluteX, AVL_type::label, addr)};
    }

    return {};
}

}

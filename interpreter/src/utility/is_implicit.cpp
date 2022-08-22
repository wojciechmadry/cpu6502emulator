#include "interp_utils.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_implicit(std::string_view address)
{
    bool found_char = false;
    for(const auto ch : address)
    {
        if(ch != ' ')
        {
            found_char = true;
            break;
        }
    }
    if(found_char == false)
    {
        return AddressInfo::create_address(Addressing::Implicit);
    }
    return {};
}

}
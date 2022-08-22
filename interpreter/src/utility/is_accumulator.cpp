#include "interp_utils.hpp"

namespace cpu6502::interpreter::utils{
    
std::optional<AddressInfo> is_accumulator(std::string_view address)
{
    bool found_A = false;
    for(const auto ch : address)
    {
        if(std::toupper(ch) == 'A')
        {
            if(found_A)
            {
                found_A = false;
                break;
            }
            found_A = true;
        }
        else if (ch != ' ')
        {
            found_A = false;
            break;
        }
    }

    if(found_A == true)
    {
        return AddressInfo::create_address(Addressing::Accumulator);
    }

    return {};
}

}
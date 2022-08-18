#include <cctype>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <unordered_map>

#include "utility.hpp"

#include <fmt/core.h> // remove this

namespace cpu6502::interpreter::utils
{



std::vector<cpu6502::interpreter::AddressInfo> get_address_info(std::string_view address)
{
    std::vector<AddressInfo> ai;
    std::vector<std::optional<AddressInfo>> ai_optional;

    // Find keywords
    const auto found_open_bracket =  address.find('(');
    const auto found_close_bracket =  address.find(')');
    const auto found_dolar =  address.find('$');
    const auto found_hash =  address.find('#');
    const auto found_comma =  address.find(',');
    
    // Value between bracket
    std::string value_in_bracekt = {""};

    if(found_close_bracket > found_open_bracket 
    && found_close_bracket != std::string::npos
    && found_open_bracket != std::string::npos)
    {
        for(std::size_t i = found_open_bracket + 1u ;i < found_close_bracket; ++i)
        {
            value_in_bracekt += address[i];
        }
    }

    // Check 'Implicit' addressing mode
    ai_optional.emplace_back(is_implicit(address));


    // Check 'Accumulator' addressing mode
    ai_optional.emplace_back(is_accumulator(address));

    // Check 'Immediate' addressing mode
    ai_optional.emplace_back(is_immediate(address, found_hash));


    // Check 'ZeroPage' or 'Absolute' addressing mode
    auto zero_page_or_absolute = is_zero_page_or_absolute(address, found_dolar);
    ai_optional.emplace_back(std::move(zero_page_or_absolute.first));
    ai_optional.emplace_back(std::move(zero_page_or_absolute.second));

    // Check 'ZeroPageX', 'Absolute X' addressing mode
    auto zero_page_x_or_absolute_x = is_zero_page_x_or_absolute_x(address, found_dolar, found_comma);
    ai_optional.emplace_back(std::move(zero_page_x_or_absolute_x.first));
    ai_optional.emplace_back(std::move(zero_page_x_or_absolute_x.second));

    // Check 'ZeroPageY', 'Absolute Y' addressing mode
    auto zero_page_y_or_absolute_y = is_zero_page_y_or_absolute_y(address, found_dolar, found_comma);
    ai_optional.emplace_back(std::move(zero_page_y_or_absolute_y.first));
    ai_optional.emplace_back(std::move(zero_page_y_or_absolute_y.second));

    // Check 'Relative' addressing mode
    ai_optional.emplace_back(is_relative(address));


    // Check 'Indirect' addressing mode
    ai_optional.emplace_back(is_indirect(address, value_in_bracekt));

    // Check 'IndirectX' addressing mode
    ai_optional.emplace_back(is_indirect_x(address, value_in_bracekt));

    // Check 'IndirectY' addressing mode
    ai_optional.emplace_back(is_indirect_y(address, value_in_bracekt));

    std::for_each(std::begin(ai_optional), std::end(ai_optional), [&](auto& optional_address)
    {
        if(optional_address.has_value())
        {
            ai.emplace_back(std::move(optional_address.value()));
        }
    });

    return ai;
}

cpu6502::interpreter::InstructionInfo get_instruction(std::string_view ins)
{

    if(ins.size() != 3)
    {
        return {};
    }


    std::string instr_name{ins};

    for(auto& ch : instr_name)
    {
        ch = static_cast<char>(std::toupper(static_cast<int>(ch)));
    }
    
    const auto& map_of_operations = get_opcode_map();

    const auto found_addressing = map_of_operations.find(instr_name);

    if(found_addressing != map_of_operations.end())
    {
        return found_addressing->second;
    };

    return {};
}

bool is_number(const char ch, const VALUE_TYPE value_type)
{
    switch(value_type)
    {
        case VALUE_TYPE::binary:
        {
            return ch == '0' || ch == '1';
        }
        case VALUE_TYPE::decimal:
        {
            return ch >= '0' && ch <= '9';
        }
        case VALUE_TYPE::hex:
        {
            const auto upp_ch = std::toupper(ch);
            return (ch >= '0' && ch <= '9') || (upp_ch >= 'A' && upp_ch <= 'F');
        }
    }
    return false;
}

bool is_propper_label(std::string_view label)
{
    for(const auto ch : label)
    {
        const auto ch_up = std::toupper(ch);
        const auto is_letter = ch_up >= 'A' && ch_up <= 'Z';
        const auto is_number = ch_up >= '0' && ch_up <= '9';
        const auto is_space = ch == ' ';
        const auto is_underscore = ch == '_';
        if(!is_letter && !is_space && !is_underscore && !is_number)
        {
            return false;
        }
    }
    return true;
}

void remove_space_front_end(std::string& str)
{
    while(str.size() > 0 && str[str.size() - 1] == ' ')
    {
        str.pop_back();
    }

    std::size_t remove_front {0u};
    while(remove_front < str.size() && str[remove_front] == ' ')
    {
        ++remove_front;
    }
    str.erase(0, remove_front);
}

}
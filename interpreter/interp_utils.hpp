#ifndef INTERPRETER_UTILITY
#define INTERPRETER_UTILITY

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "instruction.hpp"

namespace cpu6502::interpreter::utils {
enum class DebugModeNextCommand { GoLeft, GoRight };

cpu6502::interpreter::InstructionInfo get_instruction(std::string_view ins);

std::vector<cpu6502::interpreter::AddressInfo> get_address_info(
    std::string_view address,
    const std::vector<InstructionInfo::SmallAddressInfo> &possible_addressing);

const std::unordered_map<std::string, InstructionInfo> &get_opcode_map();

std::optional<AddressInfo> is_implicit(std::string_view address);

std::optional<AddressInfo> is_accumulator(std::string_view address);

std::optional<AddressInfo> is_relative(std::string_view address);

std::optional<AddressInfo> is_indirect(std::string_view address,
                                       std::string_view value_in_bracket);

std::optional<AddressInfo> is_indirect_x(std::string_view address,
                                         std::string_view value_in_bracket);

std::optional<AddressInfo> is_indirect_y(std::string_view address,
                                         std::string_view value_in_bracket);

std::optional<AddressInfo> is_immediate(std::string_view address,
                                        std::size_t hash_position);

std::pair<std::optional<AddressInfo>, std::optional<AddressInfo>>
is_zero_page_or_absolute(std::string_view address, std::size_t dolar_position);

std::pair<std::optional<AddressInfo>, std::optional<AddressInfo>>
is_zero_page_x_or_absolute_x(std::string_view address,
                             std::size_t dolar_position,
                             std::size_t comma_position);

std::pair<std::optional<AddressInfo>, std::optional<AddressInfo>>
is_zero_page_y_or_absolute_y(std::string_view address,
                             std::size_t dolar_position,
                             std::size_t comma_position);

bool is_number(const char ch, const VALUE_TYPE value_type);

bool is_propper_label(std::string_view label);

void remove_space_front_end(std::string &str);

} // namespace cpu6502::interpreter::utils

#endif // INTERPRETER_UTILITY

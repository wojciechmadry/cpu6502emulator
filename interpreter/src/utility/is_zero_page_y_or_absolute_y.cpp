#include "interp_utils.hpp"
#include <limits>

namespace cpu6502::interpreter::utils {

std::pair<std::optional<AddressInfo>, std::optional<AddressInfo>>
is_zero_page_y_or_absolute_y(std::string_view address,
                             std::size_t dolar_position,
                             std::size_t comma_position) {

  if (address.empty()) {
    return {};
  }
  // Check if address don't have bracket '(' ')'
  for (auto addres : address) {
    if (addres == '(' || addres == ')') {
      return {};
    }
  }

  bool is_y_addressing = false;
  const auto Y_found = address.find('Y');
  if (Y_found != std::string::npos || address.find('y') != std::string::npos) {
    is_y_addressing = true;
  }

  if (comma_position == std::string::npos) {
    is_y_addressing = false;
  } else {
    bool found_y = false;
    for (std::size_t i = comma_position + 1; i < address.size(); ++i) {
      if (std::toupper(address[i]) == 'Y') {
        found_y = true;
        break;
      } else if (address[i] != ' ') {
        break;
      }
    }
    if (!found_y) {
      is_y_addressing = false;
    }
  }

  const auto propably_label =
      address.substr(0, comma_position); // Can be label name

  if (dolar_position != std::string::npos && is_y_addressing) {
    std::string val{""};
    auto begin = address.begin() + dolar_position + 1;
    const auto end = address.begin() + comma_position;
    for (; begin != end; ++begin) {
      if (is_number(*begin, VALUE_TYPE::hex)) {
        val += *begin;
      } else {
        val.clear();
        break;
      }
    }

    if (!val.empty()) {
      std::uint32_t iaddr = 0;
      try {
        iaddr = static_cast<std::uint32_t>(std::stoul(val, nullptr, 16));
      } catch (const std::exception &) {
        iaddr = std::numeric_limits<std::uint32_t>::max();
      }

      if (iaddr != std::numeric_limits<std::uint32_t>::max()) {
        return {AddressInfo::create_address(Addressing::ZeroPageY,
                                            AVL_type::address, val),
                AddressInfo::create_address(Addressing::AbsoluteY,
                                            AVL_type::address, val)};
      }
    }
  } else if (is_propper_label(propably_label) && is_y_addressing) {
    std::string addr{propably_label};
    remove_space_front_end(addr);
    return {AddressInfo::create_address(Addressing::ZeroPageY, AVL_type::label,
                                        addr),
            AddressInfo::create_address(Addressing::AbsoluteY, AVL_type::label,
                                        addr)};
  }

  return {};
}

} // namespace cpu6502::interpreter::utils

#ifndef CPU6502_GUI_UTILS_HPP
#define CPU6502_GUI_UTILS_HPP

#include <QString>
#include <cstdint>
#include <optional>
#include <functional>
#include <qgroupbox.h>

namespace constant {
static constexpr auto true_str = "true";
static constexpr auto false_str = "false";
}

namespace utils{
    QString toHex(std::uint32_t val);

    std::optional<std::uint32_t> toUint32(const QString& qstr);

    template<typename ClassToFind>
    std::optional<std::reference_wrapper<ClassToFind>> searchGroupBox(QGroupBox* groupBox)
    {   
        if(groupBox == nullptr)
        {
            return {};
        }
        auto allChildrens = groupBox->children();
        for(auto child : allChildrens)
        {
            auto classFound = dynamic_cast<ClassToFind*>(child);
            if(classFound)
            {
                return *classFound;
            }
        }
        return {};
    }
}

#endif  // CPU6502_GUI_UTILS_HPP

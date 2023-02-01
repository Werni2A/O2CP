#ifndef TRAILINGPROPERTIES_HPP
#define TRAILINGPROPERTIES_HPP


#include <cstdint>
#include <ostream>
#include <string>

#include <fmt/core.h>
#include <nameof.hpp>

#include "CommonBase.hpp"


class TrailingProperties : public CommonBase
{
public:

    TrailingProperties(ParserContext& aCtx) : CommonBase{aCtx}, normalName{}, convertName{}
    { }

    std::string to_string() const override;

    void read(FileFormatVersion aVersion = FileFormatVersion::Unknown) override;

    std::string normalName;
    std::string convertName;
};


[[maybe_unused]]
static std::string to_string(const TrailingProperties& aObj)
{
    std::string str;

    str += fmt::format("{}:\n", nameof::nameof_type<decltype(aObj)>());
    str += fmt::format("{}normalName  = {}\n", indent(1), aObj.normalName);
    str += fmt::format("{}convertName = {}\n", indent(1), aObj.convertName);

    return str;
}


inline std::string TrailingProperties::to_string() const
{
    return ::to_string(*this);
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const TrailingProperties& aVal)
{
    aOs << to_string(aVal);

    return aOs;
}


#endif // TRAILINGPROPERTIES_HPP




#ifndef ELLIPSE_H
#define ELLIPSE_H


#include <cstdint>
#include <optional>
#include <ostream>
#include <string>

#include <fmt/core.h>
#include <nameof.hpp>

#include "../Enums/HatchStyle.hpp"
#include "../Enums/FillStyle.hpp"
#include "../Enums/LineStyle.hpp"
#include "../Enums/LineWidth.hpp"


struct Ellipse
{
    static size_t getExpectedStructSize(FileFormatVersion aVersion);

    void setLineStyle(const LineStyle& aVal)
    {
        mLineStyle = std::make_optional<LineStyle>(aVal);
    }

    LineStyle getLineStyle() const
    {
        return mLineStyle.value_or(LineStyle::Solid);
    }

    void setLineWidth(const LineWidth& aVal)
    {
        mLineWidth = std::make_optional<LineWidth>(aVal);
    }

    LineWidth getLineWidth() const
    {
        return mLineWidth.value_or(LineWidth::Default);
    }

    void setFillStyle(const FillStyle& aVal)
    {
        mFillStyle = std::make_optional<FillStyle>(aVal);
    }

    FillStyle getFillStyle() const
    {
        return mFillStyle.value_or(FillStyle::None);
    }

    void setHatchStyle(const HatchStyle& aVal)
    {
        mHatchStyle = std::make_optional<HatchStyle>(aVal);
    }

    HatchStyle getHatchStyle() const
    {
        return mHatchStyle.value_or(HatchStyle::NotValid);
    }

    int32_t x1;
    int32_t y1;

    int32_t x2;
    int32_t y2;

private:

    std::optional<LineStyle>  mLineStyle;
    std::optional<LineWidth>  mLineWidth;

    std::optional<FillStyle>  mFillStyle;
    std::optional<HatchStyle> mHatchStyle;
};


[[maybe_unused]]
static std::string to_string(const Ellipse& aObj)
{
    std::string str;

    str += fmt::format("{}:\n", nameof::nameof_type<decltype(aObj)>());
    str += fmt::format("{}x1 = {}\n", indent(1), aObj.x1);
    str += fmt::format("{}y1 = {}\n", indent(1), aObj.y1);
    str += fmt::format("{}x2 = {}\n", indent(1), aObj.x2);
    str += fmt::format("{}y2 = {}\n", indent(1), aObj.y2);
    str += fmt::format("{}lineStyle  = {}\n", indent(1), to_string(aObj.getLineStyle()));
    str += fmt::format("{}lineWidth  = {}\n", indent(1), to_string(aObj.getLineWidth()));
    str += fmt::format("{}fillStyle  = {}\n", indent(1), to_string(aObj.getFillStyle()));
    str += fmt::format("{}hatchStyle = {}\n", indent(1), to_string(aObj.getHatchStyle()));

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const Ellipse& aVal)
{
    aOs << to_string(aVal);

    return aOs;
}


#endif // ELLIPSE_H
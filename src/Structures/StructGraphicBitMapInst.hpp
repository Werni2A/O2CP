#ifndef STRUCTGRAPHICBITMAPEINST_HPP
#define STRUCTGRAPHICBITMAPEINST_HPP


#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>

#include <fmt/core.h>
#include <nameof.hpp>

#include "General.hpp"
#include "Structures/StructGraphicInst.hpp"


class StructGraphicBitMapInst : public StructGraphicInst
{
public:

    StructGraphicBitMapInst(StreamContext& aCtx) : StructGraphicInst{aCtx}
    { }

    std::string to_string() const override;

    void read(FileFormatVersion aVersion = FileFormatVersion::Unknown) override;

    // void accept(Visitor& aVisitor) const override
    // {
    //     aVisitor.visit(*this);
    // }

    Structure getObjectType() const override
    {
        return Structure::GraphicBitMapInst;
    }
};


[[maybe_unused]]
static std::string to_string(const StructGraphicBitMapInst& aObj)
{
    return aObj.to_string();
}


inline std::string StructGraphicBitMapInst::to_string() const
{
    std::string str;

    str += fmt::format("{}:\n", nameof::nameof_type<decltype(*this)>());

    str += StructGraphicInst::to_string();

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const StructGraphicBitMapInst& aVal)
{
    aOs << to_string(aVal);

    return aOs;
}


#endif // STRUCTGRAPHICBITMAPEINST_HPP
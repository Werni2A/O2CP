#include <cstdint>
#include <ostream>
#include <string>

#include <nameof.hpp>

#include "Enums/Primitive.hpp"
#include "Enums/Structure.hpp"
#include "FutureData.hpp"
#include "General.hpp"
#include "Structures/StructSthInPages0.hpp"


// @todo Probably a wrapper for Inst (Instances)
void StructSthInPages0::read(FileFormatVersion aVersion)
{
    auto& ds = mCtx.get().mDs.get();

    spdlog::debug(getOpeningMsg(getMethodName(this, __func__), ds.getCurrentOffset()));

    FutureDataLst localFutureLst{mCtx};

    auto_read_prefixes(Structure::SthInPages0, localFutureLst);

    readPreamble();

    localFutureLst.checkpoint();

    read_raw(aVersion, localFutureLst);

    localFutureLst.sanitizeCheckpoints();

    spdlog::debug(getClosingMsg(getMethodName(this, __func__), ds.getCurrentOffset()));
    spdlog::trace(to_string());
}


void StructSthInPages0::read_raw(FileFormatVersion /* aVersion */, FutureDataLst& aLocalFutureLst)
{
    auto& ds = mCtx.get().mDs.get();

    spdlog::debug(getOpeningMsg(getMethodName(this, __func__), ds.getCurrentOffset()));

    name = ds.readStringLenZeroTerm();

    spdlog::trace("name = {}", name);

    someStr0 = ds.readStringLenZeroTerm();

    spdlog::trace("someStr0 = {}", someStr0);

    aLocalFutureLst.checkpoint();

    color = ToColor(ds.readUint32());

    spdlog::trace("color = {}", ::to_string(color));

    const uint16_t lenPrimitives = ds.readUint16();

    spdlog::trace("lenPrimitives = {}", lenPrimitives);

    for(size_t i = 0u; i < lenPrimitives; ++i)
    {
        const Primitive primitive = readPrefixPrimitive();

        readPrimitive(primitive);
    }

    // @todo Looks like it has one of {0, 8, 16 , 20} Byte in size
    //       16 Byte could be the coordinates with 4 byte each value
    //       20 Byte could be the 4 Byte coordinates with with some additional value
    spdlog::trace("Calculating {} - {} == 8", aLocalFutureLst.cbegin()->getStopOffset(), ds.getCurrentOffset());
    if(aLocalFutureLst.getNextCheckpointPos().value_or(0U) - ds.getCurrentOffset() == std::size_t{8U})
    {
        spdlog::trace("Probably coordinates");

        const int16_t x1 = ds.readInt16();
        spdlog::trace("x1 = {}", x1);

        const int16_t y1 = ds.readInt16();
        spdlog::trace("y1 = {}", y1);

        const int16_t x2 = ds.readInt16();
        spdlog::trace("x2 = {}", x2);

        const int16_t y2 = ds.readInt16();
        spdlog::trace("y2 = {}", y2);
    }
    else
    {
        aLocalFutureLst.readUntilNextFutureData("See FuturData of StructSthInPages0 - raw");
    }

    aLocalFutureLst.checkpoint();

    spdlog::debug(getClosingMsg(getMethodName(this, __func__), ds.getCurrentOffset()));
}
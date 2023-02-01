#include <cstdint>
#include <ostream>
#include <string>

#include <nameof.hpp>

#include "Enums/Structure.hpp"
#include "General.hpp"
#include "Structures/StructBusEntry.hpp"


void StructBusEntry::read(FileFormatVersion /* aVersion */)
{
    spdlog::debug(getOpeningMsg(getMethodName(this, __func__), mDs.get().getCurrentOffset()));

    FutureDataLst localFutureLst{mDs};

    auto_read_prefixes(Structure::BusEntry, localFutureLst);

    readPreamble();

    color = ToColor(mDs.get().readUint32());

    spdlog::trace("color = {}", ::to_string(color));

    startX = mDs.get().readInt32();
    startY = mDs.get().readInt32();

    spdlog::trace("startX = {}", startX);
    spdlog::trace("startY = {}", startY);

    endX = mDs.get().readInt32();
    endY = mDs.get().readInt32();

    spdlog::trace("endX = {}", endX);
    spdlog::trace("endY = {}", endY);

    localFutureLst.readRestOfStructure();

    spdlog::debug(getClosingMsg(getMethodName(this, __func__), mDs.get().getCurrentOffset()));
    spdlog::trace(to_string());
}
#include <cstdint>
#include <ostream>
#include <string>

#include <nameof.hpp>

#include "Container.hpp"
#include "Enums/Structure.hpp"
#include "General.hpp"
#include "GenericParser.hpp"
#include "Structures/StructGlobal.hpp"


void StructGlobal::read(FileFormatVersion /* aVersion */)
{
    auto& ds = mCtx.mDs;
    GenericParser parser{mCtx};

    spdlog::debug(getOpeningMsg(getMethodName(this, __func__), ds.getCurrentOffset()));

    FutureDataLst localFutureLst{mCtx};

    parser.auto_read_prefixes(Structure::Global, localFutureLst);

    StructGraphicInst::read(localFutureLst);

    localFutureLst.sanitizeCheckpoints();

    spdlog::debug(getClosingMsg(getMethodName(this, __func__), ds.getCurrentOffset()));
    spdlog::trace(to_string());
}
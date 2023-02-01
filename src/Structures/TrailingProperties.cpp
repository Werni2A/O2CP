#include <cstdint>
#include <ostream>
#include <string>

#include <nameof.hpp>

#include "Enums/LineStyle.hpp"
#include "Enums/LineWidth.hpp"
#include "General.hpp"
#include "Structures/TrailingProperties.hpp"


void TrailingProperties::read(FileFormatVersion /* aVersion */)
{
    spdlog::debug(getOpeningMsg(getMethodName(this, __func__), mDs.get().getCurrentOffset()));

    // @todo use enum for the view (normal/convert)
    const uint16_t viewNumber = mDs.get().readUint16(); // @todo I assume that this is the amount of views
                                               // the symbol has. Typically 1 (.Normal) or maybe
                                               // 2 with (.Normal and .Convert)
                                               // @todo Add to obj

    spdlog::trace("viewNumber = {}", viewNumber);

    if(viewNumber == 1U) // Contains ".Normal"
    {
        normalName = mDs.get().readStringLenZeroTerm();
    }

    if(viewNumber == 2U) // Contains ".Normal" and ".Convert"
    {
        normalName = mDs.get().readStringLenZeroTerm();
        convertName = mDs.get().readStringLenZeroTerm();
    }

    spdlog::trace("normalName  = {}", normalName);
    spdlog::trace("convertName = {}", convertName);

    if(viewNumber != 1U && viewNumber != 2U)
    {
        const std::string msg = fmt::format("viewNumber = {} but expected it to be 1 or 2!",
            viewNumber);

        spdlog::error(msg);
        throw std::runtime_error(msg);
    }

    // localFutureLst.readRestOfStructure();

    spdlog::debug(getClosingMsg(getMethodName(this, __func__), mDs.get().getCurrentOffset()));
    spdlog::trace(to_string());
}
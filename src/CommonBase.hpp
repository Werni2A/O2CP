#ifndef COMMONBASE_HPP
#define COMMONBASE_HPP


#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "DataStream.hpp"
#include "Enums/Primitive.hpp"
#include "Enums/Structure.hpp"
#include "FutureData.hpp"
#include "General.hpp"


class PrimBase;


class CommonBase
{
public:
    CommonBase(DataStream& aDs) : mDs{aDs}, mFileFormatVersion{FileFormatVersion::C}
    { }

    virtual std::string to_string() const = 0;

    virtual void read(FileFormatVersion aVersion = FileFormatVersion::Unknown) = 0;

    void discard_until_preamble();

    Structure auto_read_prefixes();

    Structure auto_read_prefixes(Structure aExpectedStruct);

    Structure auto_read_prefixes(const std::vector<Structure>& aExpectedOneOfStruct);

    Structure read_prefixes(size_t aNumber, bool aPrediction = false);

    std::pair<Structure, uint32_t> read_single_prefix();

    std::pair<Structure, uint32_t> read_single_prefix_short();

    void readPreamble();
    Primitive readPrefixPrimitive();

    std::optional<FutureData> getFutureData();

    void sanitizeThisFutureSize(std::optional<FutureData> aThisFuture);

    std::optional<FutureData> checkTrailingFuture();

    void readOptionalTrailingFuture();

    void checkInterpretedDataLen(const std::string &aFuncName, size_t aStartOffset, size_t aEndOffset, size_t aExpectedLen);

    FileFormatVersion predictVersion();

    std::unique_ptr<PrimBase> readPrimitive();
    std::unique_ptr<PrimBase> readPrimitive(Primitive aPrimitive);

    std::unique_ptr<CommonBase> readStructure();
    std::unique_ptr<CommonBase> readStructure(Structure aStructure);

protected:
    std::reference_wrapper<DataStream> mDs;

    FileFormatVersion mFileFormatVersion;
};


extern FutureDataLst mFutureDataLst;


#include "Primitives/PrimBase.hpp"


#endif // COMMONBASE_HPP
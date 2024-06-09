#ifndef RECORD_HPP
#define RECORD_HPP


#include <string>

#include "Enums/Structure.hpp"
#include "General.hpp"
#include "StreamContext.hpp"


class Base
{
public:
    Base(StreamContext& aCtx) : mCtx{aCtx}
    { }

    virtual std::string to_string() const = 0;

    virtual void read(FileFormatVersion aVersion = FileFormatVersion::Unknown) = 0;

protected:
    StreamContext& mCtx;
};


class Record : public Base
{
public:
    Record(StreamContext& aCtx) : Base{aCtx}
    { }

    virtual Structure getObjectType() const = 0;
};


// Base class for structures that do not belong to Objects or Primitives
class Other : public Base
{
public:
    Other(StreamContext& aCtx) : Base{aCtx}
    { }
};


#endif // RECORD_HPP
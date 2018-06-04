#include "Vec2Arg.h"

ALA_CLASS_SOURCE_1(Vec2Arg, ala::MessageArgs)

Vec2Arg::Vec2Arg(const ala::Vec2& payload)
{
  _payload = payload;
}

const ala::Vec2& Vec2Arg::getPayload() const
{
  return _payload;
}

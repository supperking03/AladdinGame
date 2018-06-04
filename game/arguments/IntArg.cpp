#include "IntArg.h"

ALA_CLASS_SOURCE_1(IntArg, ala::MessageArgs)

IntArg::IntArg(const int payload)
{
  _payload = payload;
}

int IntArg::getPayload() const
{
  return _payload;
}

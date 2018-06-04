#ifndef __INT_MESSAGE_ARGS_H__
#define __INT_MESSAGE_ARGS_H__

#include <aladdin.h>


ALA_CLASS_HEADER_1(IntArg, ala::MessageArgs)
public:
  IntArg(const int payload);

  int getPayload() const;

private:
  int _payload;
};
#endif //!__INT_MESSAGE_ARGS_H__

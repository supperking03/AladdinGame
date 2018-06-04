#ifndef __VEC2_MESSAGE_ARGS_H__
#define __VEC2_MESSAGE_ARGS_H__

#include <aladdin.h>


ALA_CLASS_HEADER_1(Vec2Arg, ala::MessageArgs)
public:
  Vec2Arg(const ala::Vec2& payload);

  const ala::Vec2& getPayload() const;

private:
  ala::Vec2 _payload;
};
#endif //!__VEC2_MESSAGE_ARGS_H__

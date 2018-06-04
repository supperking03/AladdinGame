#ifndef __ALADDIN_EXTRA_MOVE_BY_H__
#define __ALADDIN_EXTRA_MOVE_BY_H__

#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(MoveBy, ala::Action)
private:
  float _eslapsedTime;
  float _duration;
  Vec2 _velocity;

public:
  MoveBy( const Vec2& distance, const float duration );

protected:
  void onStart() override;

  void onUpdate( const float delta ) override;
};
}

#endif //!__ALADDIN_EXTRA_MOVE_BY_H__

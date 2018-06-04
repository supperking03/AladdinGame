#ifndef __ALADDIN_EXTRA_ROTATE_BY_H__
#define __ALADDIN_EXTRA_ROTATE_BY_H__

#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(RotateBy, ala::Action)
private:
  float _eslapsedTime;
  float _duration;
  float _velocity;

public:
  RotateBy( const float angle, const float duration );

protected:
  void onStart() override;

  void onUpdate( const float delta ) override;
};
}

#endif //!__ALADDIN_EXTRA_ROTATE_BY_H__

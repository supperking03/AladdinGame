#ifndef __ALADDIN_EXTRA_BLINK_H__
#define __ALADDIN_EXTRA_BLINK_H__

#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Blink, ala::Action)
private:
  int _count;
  float _interval;
  float _eslapsedTime;
  int _eslapsedCount;
  bool _previousVisible;

public:
  Blink( const float interval, const int count = -1 );

protected:
  void onStart() override;

  void onUpdate( const float delta ) override;
};
}

#endif //!__ALADDIN_EXTRA_BLINK_H__

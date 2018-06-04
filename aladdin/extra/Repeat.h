#ifndef __ALADDIN_EXTRA_REPEAT_H__
#define __ALADDIN_EXTRA_REPEAT_H__

#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Repeat, ala::Action)
private:
  Action* _action;
  int _count;
  int _eslapsedCount;

public:
  Repeat( Action* action, const int count = -1 );

protected:
  void onStart() override;
  
  void onUpdate( float delta ) override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_EXTRA_REPEAT_H__

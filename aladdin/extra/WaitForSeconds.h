#ifndef __ALADDIN_EXTRA_WAIT_FOR_SECONDS_H__
#define __ALADDIN_EXTRA_WAIT_FOR_SECONDS_H__

#include "Action.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(WaitForSeconds, ala::Action)
private:
  float _elapsedTime;
  float _totalWaitTime;
public:
  WaitForSeconds(const float totalWaitTime);

protected:
  void onStart() override;

  void onUpdate(const float delta) override;
};
}

#endif //!__ALADDIN_EXTRA_WAIT_FOR_SECONDS_H__

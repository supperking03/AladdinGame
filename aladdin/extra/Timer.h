#ifndef __ALADDIN_EXTRA_TIMER_H__
#define __ALADDIN_EXTRA_TIMER_H__

#include "ExtraInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1( Timer, ala::GameObjectComponent)
private:
  float _timer;

public:
  Timer( ala::GameObject* gameObject, const std::string& name = "" );

  void start( const float time );

  bool isDone() const;

protected:
  void onUpdate( const float delta ) override;
};
}

#endif //!__ALADDIN_EXTRA_TIMER_H__

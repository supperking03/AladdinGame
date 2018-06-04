#ifndef __ALADDIN_EXTRA_SEQUENCE_H__
#define __ALADDIN_EXTRA_SEQUENCE_H__

#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Sequence, ala::Action)
private:
  std::vector<Action*>::const_iterator _currentActionIterator;

  std::vector<Action*> _actions;

public:
  Sequence( const std::vector<Action*>& actions );

protected:
  void onStart() override;

  void onUpdate( const float delta ) override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_EXTRA_SEQUENCE_H__

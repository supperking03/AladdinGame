#ifndef __ALADDIN_EXTRA_ACTION_H__
#define __ALADDIN_EXTRA_ACTION_H__

#include "ExtraInclude.h"
#include "ActionManager.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Action, ala::Releasable)
private:
  int _state;
  ActionManager* _actionManager;

public:
  Action();

  virtual ~Action();

  bool isStarted() const;

  bool isDone() const;

  void start( ActionManager* actionManager );

  void update( const float delta );

  void release() override;

  ActionManager* getActionManager() const;

protected:
  void done();

  virtual void onStart();

  virtual void onUpdate( float delta );

  virtual void onRelease();
};
}

#endif //!__ALADDIN_EXTRA_ACTION_H__

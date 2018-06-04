#ifndef __ALADDIN_EXTRA_ACTION_MANAGER_H__
#define __ALADDIN_EXTRA_ACTION_MANAGER_H__

#include "ExtraInclude.h"

NAMESPACE_ALA
{
class Action;

ALA_CLASS_HEADER_1(ActionManager, ala::GameObjectComponent)
private:
  bool _actionsInLock;
  std::vector<Action*> _actions;
  std::vector<Action*> _actionsToAddInNextFrame;
  std::vector<Action*> _actionsToRemoveInNextFrame;

public:
  ActionManager( GameObject* gameObject, const std::string& name = "" );

  void play( Action* action );

  void stopAll();

protected:
  void onUpdate( const float delta ) override;

  void onResolvedLockedTasks() override;

  void onRelease() override;

private:
  void lockActions();

  void unlockActions();

public:
  void addAction( Action* action );

  void addActionInNextFrame( Action* action );

private:
  void doAddAction( Action* action );

public:
  void removeAction( Action* action );

  void removeActionInNextFrame( Action* action );

private:
  void doRemoveAction( Action* action );
};
}

#endif //!__ALADDIN_EXTRA_ACTION_MANAGER_H__

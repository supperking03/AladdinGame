#include "ActionManager.h"
#include "Action.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_1(ala::ActionManager, ala::GameObjectComponent)

  ActionManager::ActionManager(GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _actionsInLock(false) {}

void ActionManager::play(Action* action) {
  addAction(action);
}

void ActionManager::stopAll() {

  std::vector<Action*> actions;

  for (const auto action : _actions) {
    actions.push_back(action);
  }

  for (const auto action : actions) {
    action->release();
  }

  for (const auto action : actions) {
    removeAction(action);
  }
}

void ActionManager::onUpdate(const float delta) {
  lockActions();

  for (const auto action : _actions) {
    if (!action->isStarted()) {
      action->start(this);
    }
    else if (action->isDone()) {
      action->release();
    }
    else {
      action->update(delta);
    }
  }

  unlockActions();
}

void ActionManager::onResolvedLockedTasks() {
  for (const auto action : _actionsToAddInNextFrame) {
    doAddAction(action);
  }
  _actionsToAddInNextFrame.clear();

  for (const auto action : _actionsToRemoveInNextFrame) {
    doRemoveAction(action);
  }
  _actionsToRemoveInNextFrame.clear();
}

void ActionManager::onRelease() {
  for (const auto action : _actions) {
    action->release();
  }
}

void ActionManager::lockActions() {
  _actionsInLock = true;
}

void ActionManager::unlockActions() {
  _actionsInLock = false;
}

void ActionManager::addAction(Action* action) {
  if (isReleased() || isReleasing()) return;
  if (action == NULL) return;

  if (_actionsInLock) {
    addActionInNextFrame(action);
    return;
  }

  doAddAction(action);
}

void ActionManager::addActionInNextFrame(Action* action) {
  if (isReleased() || isReleasing()) return;
  if (action == NULL) return;

  if (!StdHelper::vectorContain(_actionsToAddInNextFrame, action)) {
    _actionsToAddInNextFrame.emplace_back(action);
  }
}

void ActionManager::doAddAction(Action* action) {
  if (!StdHelper::vectorContain(_actions, action)) {
    _actions.emplace_back(action);
  }
}

void ActionManager::removeAction(Action* action) {
  if (isReleased() || isReleasing()) return;
  if (action == NULL) return;

  if (_actionsInLock) {
    removeActionInNextFrame(action);
    return;
  }

  doRemoveAction(action);
}

void ActionManager::removeActionInNextFrame(Action* action) {
  if (isReleased() || isReleasing()) return;
  if (action == NULL) return;

  if (!StdHelper::vectorContain(_actionsToRemoveInNextFrame, action)) {
    _actionsToRemoveInNextFrame.emplace_back(action);
  }
}

void ActionManager::doRemoveAction(Action* action) {
  StdHelper::vectorErase(_actions, action);
}
}

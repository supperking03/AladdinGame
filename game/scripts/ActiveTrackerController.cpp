#include "ActiveTrackerController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(ActiveTrackerController, ala::GameObjectComponent)

ActiveTrackerController::ActiveTrackerController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _isOn(false)
{
}

ActiveTrackerController::~ActiveTrackerController()
{
}

void ActiveTrackerController::onInitialize()
{
  for (auto collider : _colliders)
  {
    if (_isOn)
    {
      collider->unignoreTag(ALADDIN_TAG);
    }
    else
    {
      collider->ignoreTag(ALADDIN_TAG);

      auto activeTracker = collider->getGameObject()->getComponentT<ActiveTrackerController>();
      if (activeTracker != NULL)
      {
        activeTracker->turnOff();
      }
    }
  }
}

void ActiveTrackerController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  if(collision.getColliderA()->getTag() != ALADDIN_TAG && collision.getColliderB()->getTag() != ALADDIN_TAG)
  {
    return;
  }
  _isOn = !_isOn;

  for (auto collider : _colliders)
  {
    if (_isOn)
    {
      collider->unignoreTag(ALADDIN_TAG);
    }
    else
    {
      collider->ignoreTag(ALADDIN_TAG);

      auto activeTracker = collider->getGameObject()->getComponentT<ActiveTrackerController>();
      if (activeTracker != NULL)
      {
        activeTracker->turnOff();
      }
    }
  }
}

void ActiveTrackerController::addCollider(ala::Collider* addedCollider)
{
  _colliders.push_back(addedCollider);
  for (auto collider : _colliders)
  {
    if (_isOn)
    {
      collider->unignoreTag(ALADDIN_TAG);
    }
    else
    {
      collider->ignoreTag(ALADDIN_TAG);

      auto activeTracker = collider->getGameObject()->getComponentT<ActiveTrackerController>();
      if(activeTracker != NULL)
      {
        activeTracker->turnOff();
      }
    }
  }
}

void ActiveTrackerController::turnOff()
{
  _isOn = false;
  for (auto collider : _colliders)
  {
    if (_isOn)
    {
      collider->unignoreTag(ALADDIN_TAG);
    }
    else
    {
      collider->ignoreTag(ALADDIN_TAG);

      auto activeTracker = collider->getGameObject()->getComponentT<ActiveTrackerController>();
      if (activeTracker != NULL)
      {
        activeTracker->turnOff();
      }
    }
  }
}

void ActiveTrackerController::turnOn()
{
  _isOn = true;
  for (auto collider : _colliders)
  {
    if (_isOn)
    {
      collider->unignoreTag(ALADDIN_TAG);
    }
    else
    {
      collider->ignoreTag(ALADDIN_TAG);
    }
  }
}

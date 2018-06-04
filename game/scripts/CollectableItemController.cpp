#include "CollectableItemController.h"
#include "../Macros.h"
#include "../arguments/IntArg.h"

ALA_CLASS_SOURCE_1(CollectableItemController, ala::GameObjectComponent)

CollectableItemController::CollectableItemController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _collidedWithAladdin(false)
{
}

CollectableItemController::~CollectableItemController()
{
}

void CollectableItemController::setValue(const std::string& value)
{
  _value = value;
}

const std::string& CollectableItemController::getValue() const
{
  return _value;
}

bool CollectableItemController::isCollidedWithAladdin() const
{
  return _collidedWithAladdin;
}

void CollectableItemController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  if ((collision.getColliderA()->getTag() == ALADDIN_TAG || collision.getColliderB()->getTag() == ALADDIN_TAG ||
    collision.getColliderA()->getTag() == ALADDIN_WEAPON_TAG || collision.getColliderB()->getTag() == ALADDIN_WEAPON_TAG) &&
    (collision.getColliderA()->getGameObject()->getTag() == ALADDIN_TAG || collision.getColliderB()->getGameObject()->getTag() == ALADDIN_TAG))
  {
    _collidedWithAladdin = true;
  }
}


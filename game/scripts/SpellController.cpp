#include "SpellController.h"
#include "../Macros.h"


ALA_CLASS_SOURCE_1(SpellController, ala::GameObjectComponent)

SpellController::SpellController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _colliedWithAladdin(false) {}


void SpellController::onTriggerEnter(const ala::CollisionInfo& collision) {
  if (collision.getColliderA()->getGameObject()->getTag() == ALADDIN_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == ALADDIN_TAG) {
    _colliedWithAladdin = true;
  }
}

bool SpellController::isCollidedWithAladdin() const
{
  return _colliedWithAladdin;
}

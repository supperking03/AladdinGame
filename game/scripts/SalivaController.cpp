#include "SalivaController.h"
#include "../Macros.h"
#include <debugapi.h>

ALA_CLASS_SOURCE_1(SalivaController, ala::GameObjectComponent)

SalivaController::SalivaController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name)
{
}

void SalivaController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject() ? collision.getColliderB() : collision.getColliderA();

  if(otherCollider->getTag() == ENEMY_TAG ||
    otherCollider->getTag() == WALL_TAG ||
    otherCollider->getTag() == GROUND_TAG)
  {
    OutputDebugString("Destroyed");
    getGameObject()->release();
  }
}
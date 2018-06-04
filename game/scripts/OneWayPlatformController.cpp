#include "OneWayPlatformController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(OneWayPlatformController, ala::GameObjectComponent)

OneWayPlatformController::OneWayPlatformController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name)
{
}

void OneWayPlatformController::addPlatform(ala::Collider* collider)
{
  const auto trigger = new ala::Collider(getGameObject(), true, collider->getOffset(), ala::Size(collider->getSize().getWidth(), collider->getSize().getHeight()), 1, 0);
  collider->ignoreTag(ALADDIN_TAG);
  collider->ignoreTag(ALADDIN_WEAPON_TAG);
  trigger->ignoreTag(WALL_TAG);
  trigger->ignoreTag(ROPE_CHECKER_TAG);
  trigger->ignoreTag(ROPE_TAG);
  trigger->ignoreTag(GROUND_TAG);
  trigger->ignoreTag(COLLECTABLE_ITEM_TAG);
  trigger->ignoreTag(HANGER_TAG);
  trigger->ignoreTag(CHARCOAL_BURNER_TAG);
  trigger->ignoreTag(ENEMY_TAG);
  trigger->ignoreTag(ENEMY_WEAPON_TAG);
  trigger->ignoreTag(ALADDIN_WEAPON_TAG);
  _colliders[trigger] = collider;
}

void OneWayPlatformController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  if(_colliders.find(collision.getColliderA()) != _colliders.end())
  {
    if(collision.getNormal().getY() != 1)
    {
      return;
    }
    _colliders[collision.getColliderA()]->unignoreTag(ALADDIN_TAG);
    _colliders[collision.getColliderA()]->unignoreTag(ALADDIN_WEAPON_TAG);
  }
  if (_colliders.find(collision.getColliderB()) != _colliders.end())
  {
    if (collision.getNormal().getY() != -1)
    {
      return;
    }
    _colliders[collision.getColliderB()]->unignoreTag(ALADDIN_TAG);
    _colliders[collision.getColliderB()]->unignoreTag(ALADDIN_WEAPON_TAG);
  }
}

void OneWayPlatformController::onTriggerExit(const ala::CollisionInfo& collision)
{
  if (_colliders.find(collision.getColliderA()) != _colliders.end())
  {
    _colliders[collision.getColliderA()]->ignoreTag(ALADDIN_TAG);
    _colliders[collision.getColliderA()]->ignoreTag(ALADDIN_WEAPON_TAG);
  }
  if (_colliders.find(collision.getColliderB()) != _colliders.end())
  {
    _colliders[collision.getColliderB()]->ignoreTag(ALADDIN_TAG);
    _colliders[collision.getColliderB()]->ignoreTag(ALADDIN_WEAPON_TAG);
  }
}

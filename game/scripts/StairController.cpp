#include "StairController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(StairController, ala::GameObjectComponent)

void StairController::onCollisionStay(const ala::CollisionInfo& collision)
{
  if(collision.getColliderA()->getTag() == ALADDIN_TAG || collision.getColliderA()->getGameObject()->getTag() == ENEMY_TAG)
  {
    auto aladdinBoundingRect = collision.getColliderA()->getBoundingRect();
    auto selfBoundingRect = collision.getColliderB()->getBoundingRect();

    if(aladdinBoundingRect.getMinY() < selfBoundingRect.getMaxY())
    {
      auto rb = collision.getColliderA()->getGameObject()->getComponentT<ala::Rigidbody>();
      rb->setPosition(rb->getPosition() + ala::Vec2(0, selfBoundingRect.getMaxY() - aladdinBoundingRect.getMinY()));
    }
  }
  else if(collision.getColliderB()->getTag() == ALADDIN_TAG || collision.getColliderB()->getGameObject()->getTag() == ENEMY_TAG)
  {
    auto aladdinBoundingRect = collision.getColliderB()->getBoundingRect();
    auto selfBoundingRect = collision.getColliderA()->getBoundingRect();

    if (aladdinBoundingRect.getMinY() < selfBoundingRect.getMaxY())
    {
      auto rb = collision.getColliderB()->getGameObject()->getComponentT<ala::Rigidbody>();
      rb->setPosition(rb->getPosition() + ala::Vec2(0, selfBoundingRect.getMaxY() - aladdinBoundingRect.getMinY()));
    }
  }
}

StairController::StairController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name)
{
}

StairController::~StairController()
{
}

void StairController::onInitialize()
{
  for(auto collider: getGameObject()->getAllComponentTs<ala::Collider>())
  {
    collider->ignoreTag(GROUND_TAG);
    collider->ignoreTag(WALL_TAG);
    collider->ignoreTag(ROPE_TAG);
    collider->ignoreTag(ROPE_CHECKER_TAG);
  }
}

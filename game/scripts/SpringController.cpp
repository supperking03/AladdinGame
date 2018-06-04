#include "SpringController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(SpringController, ala::GameObjectComponent)

SpringController::SpringController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _collidedWithAladdin(false)
{
}

void SpringController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getTag() == ALADDIN_TAG)
  {
    if (collision.getNormal().getY() == -1)
    {
      _collidedWithAladdin = true;
      auto rb = collision.getColliderA()->getGameObject()->getComponentT<ala::Rigidbody>();
      if(rb->getVelocity().getY() < 0)
      {
        rb->setVelocity(ala::Vec2(0, 450.f));
      }
      else
      {
        rb->addVelocity(ala::Vec2(0, 450.f));
      }
     
      collision.getColliderA()->getGameObject()->getComponentT<ala::StateManager>()->changeState("spin");
    }
  }
  else if (collision.getColliderB()->getTag() == ALADDIN_TAG)
  {
    if (collision.getNormal().getY() == 1)
    {
      _collidedWithAladdin = true;
      auto rb = collision.getColliderB()->getGameObject()->getComponentT<ala::Rigidbody>();
      if (rb->getVelocity().getY() < 0)
      {
        rb->setVelocity(ala::Vec2(0, 450.f));
      }
      else
      {
        rb->addVelocity(ala::Vec2(0, 450.f));
      }

      collision.getColliderB()->getGameObject()->getComponentT<ala::StateManager>()->changeState("spin");
    }
  }
}

void SpringController::onTriggerExit(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getTag() == ALADDIN_TAG)
  {
    _collidedWithAladdin = false;
  }
  else if (collision.getColliderB()->getTag() == ALADDIN_TAG)
  {
    _collidedWithAladdin = false;
  }
}

bool SpringController::isCollidedWithAladdin() const
{
  return _collidedWithAladdin;
}

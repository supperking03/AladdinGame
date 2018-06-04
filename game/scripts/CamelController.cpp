#include "CamelController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(CamelController, ala::GameObjectComponent)

CamelController::CamelController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
    _collidedWithAladdin(false)
{
}

void CamelController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getTag() == ALADDIN_TAG)
  {
    if (collision.getNormal().getY() == -1)
    {
      _collidedWithAladdin = true;
      collision.getColliderA()->getGameObject()->getComponentT<ala::Rigidbody>()->addVelocity(ala::Vec2(0, 75.f));
      collision.getColliderA()->getGameObject()->getComponentT<ala::StateManager>()->changeState("jump");
    }
  }
  else if (collision.getColliderB()->getTag() == ALADDIN_TAG)
  {
    if (collision.getNormal().getY() == 1)
    {
      _collidedWithAladdin = true;
      collision.getColliderB()->getGameObject()->getComponentT<ala::Rigidbody>()->addVelocity(ala::Vec2(0, 75.f));
      collision.getColliderB()->getGameObject()->getComponentT<ala::StateManager>()->changeState("jump");
    }
  }
}

void CamelController::onTriggerExit(const ala::CollisionInfo& collision)
{
  if(collision.getColliderA()->getTag() == ALADDIN_TAG)
  {
    _collidedWithAladdin = false;
  }
  else if(collision.getColliderB()->getTag() == ALADDIN_TAG)
  {
    _collidedWithAladdin = false;
  }
}

void CamelController::puffSaliva() const
{

  ala::GameManager::get()->getPrefab("Saliva")->instantiate()
    ->getTransform()
    ->setPosition(getGameObject()->getTransform()->getPosition() +
                           ala::Vec2(85, -10));

}

bool CamelController::isCollidedWithAladdin() const
{
  return _collidedWithAladdin;
}

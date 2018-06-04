#include "FallingPlatformController.h"
#include "../Macros.h"


ALA_CLASS_SOURCE_1(FallingPlatformController, ala::GameObjectComponent)

FallingPlatformController::FallingPlatformController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _collidedWithGround(false), _collidedWithAladdin(false), _startPosition(ala::Vec2(0,0)) {}

const ala::Vec2& FallingPlatformController::getStartPosition() const
{
  return _startPosition;
}

bool FallingPlatformController::isCollidedWithGround() const {
  return _collidedWithGround;
}

void FallingPlatformController::onCollisionStay(const ala::CollisionInfo& collision) {
  const auto other = collision.getColliderA()->getGameObject() == getGameObject() ? collision.getColliderB() : collision.getColliderA();
  if (other->getTag() == GROUND_TAG) {
    _collidedWithGround = true;
  }

  if (collision.getColliderA()->getGameObject()->getTag() == ALADDIN_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == ALADDIN_TAG) {
    _collidedWithAladdin = true;
  }
}

void FallingPlatformController::onInitialize()
{
  _startPosition = getGameObject()->getTransform()->getPosition();
}

void FallingPlatformController::onCollisionExit(const ala::CollisionInfo& collision)
{

}

void FallingPlatformController::startAladdinCheck()
{
  _collidedWithAladdin = false;
}

void FallingPlatformController::startGroundCheck()
{
  _collidedWithGround = false;
}

bool FallingPlatformController::isCollidedWithAladdin() const
{
  return _collidedWithAladdin;
}

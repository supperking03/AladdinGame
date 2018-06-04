#include "ThrowingAppleController.h"
#include "../Macros.h"


ALA_CLASS_SOURCE_1(ThrowingAppleController, ala::GameObjectComponent)

ThrowingAppleController::ThrowingAppleController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), 
_collidedWithGround(false), 
_collidedWithWall(false), 
_collidedWithEnemy(false),
_collidedWithMapBlocker(false)
{
  
}


bool ThrowingAppleController::isCollidedWithGround() const 
{
  return _collidedWithGround;
}

void ThrowingAppleController::onTriggerEnter(const ala::CollisionInfo& collision) 
{
  if (collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG) {
    _collidedWithGround = true;
  }

  if (collision.getColliderA()->getGameObject()->getTag() == ENEMY_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == ENEMY_TAG) {
    _collidedWithEnemy = true;
  }
  if (collision.getColliderA()->getGameObject()->getTag() == WALL_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == WALL_TAG) {
    _collidedWithWall = true;
  }
}

bool ThrowingAppleController::isCollidedWithEnemy() const
{
  return _collidedWithEnemy;
}

bool ThrowingAppleController::isCollidedWithWall() const
{
  return _collidedWithWall;
}

bool ThrowingAppleController::isCollidedWithMapBlocker() const
{
  return _collidedWithMapBlocker;
}

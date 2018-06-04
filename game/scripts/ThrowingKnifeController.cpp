#include "ThrowingKnifeController.h"
#include "../Macros.h"


ALA_CLASS_SOURCE_1(ThrowingKnifeController, ala::GameObjectComponent)

ThrowingKnifeController::ThrowingKnifeController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), 
  _collidedWithGround(false), 
  _collidedWithWall(false),
  _collidedWithEnemy(false), 
  _collidedWithAladdin(false)
{
  
}


bool ThrowingKnifeController::isCollidedWithGround() const 
{
  return _collidedWithGround;
}

void ThrowingKnifeController::onTriggerEnter(const ala::CollisionInfo& collision) 
{
  if (collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG) 
  {
    _collidedWithGround = true;
  }

  if (collision.getColliderA()->getGameObject()->getTag() == ENEMY_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == ENEMY_TAG) 
  {
    _collidedWithEnemy = true;
  }
  if (collision.getColliderA()->getGameObject()->getTag() == WALL_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == WALL_TAG) {
    _collidedWithWall = true;
  }

  if (collision.getColliderA()->getTag() == ALADDIN_TAG ||
    collision.getColliderB()->getTag() == ALADDIN_TAG) 
  {
    _collidedWithAladdin = true;
  }
}

bool ThrowingKnifeController::isCollidedWithEnemy() const
{
  return _collidedWithEnemy;
}

bool ThrowingKnifeController::isCollidedWithWall() const
{
  return _collidedWithWall;
}

bool ThrowingKnifeController::isCollidedWithAladdin() const
{
  return _collidedWithAladdin;
}

#include "PotController.h"
#include "../Macros.h"
#include "WeaponController.h"


ALA_CLASS_SOURCE_1(PotController, ala::GameObjectComponent)

PotController::PotController(ala::GameObject* gameObject, int health, const std::string& name)
  : GameObjectComponent(gameObject, name), _collidedWithGround(false), _colliedWithAladdin(false), _health(health), _transform(NULL) {}


bool PotController::isCollidedWithGround() const {
  return _collidedWithGround;
}

void PotController::onTriggerEnter(const ala::CollisionInfo& collision) {
  
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
    ? collision.getColliderB()
    : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
    ? collision.getColliderB()
    : collision.getColliderA();

  if (selfCollider->getTag() == ENEMY_WEAPON_TAG)
  {
    if ((otherCollider->getTag() == ALADDIN_WEAPON_TAG)) {
      onHit(otherCollider->getGameObject()->getComponentT<WeaponController>()->getDamage() - 1);
    }
  }
  
  if (collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG) {
    _collidedWithGround = true;
  }

  if (collision.getColliderA()->getGameObject()->getTag() == ALADDIN_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == ALADDIN_TAG) {
    _colliedWithAladdin = true;
  }
}

void PotController::onCollisionExit(const ala::CollisionInfo& collision)
{
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
    ? collision.getColliderB()
    : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
}

bool PotController::isCollidedWithAladdin() const
{
  return _colliedWithAladdin;
}

void PotController::onInitialize()
{
  _transform = getGameObject()->getTransform();
}

int PotController::getHealth() const
{
  return _health;
}

void PotController::setHealth(const int health)
{
  _health = health;
}

void PotController::onOutOfHealth() const
{
  ala::GameManager::get()->getPrefab("Explosion")->instantiate(_transform->getPosition());
  getGameObject()->release();
}

void PotController::onHit(const int damage)
{
  _health -= damage;
  if (_health <= 0)
  {
    onOutOfHealth();
  }
}

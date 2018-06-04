#include "EnemyController.h"
#include "EnemyDirectionController.h"
#include "../Macros.h"
#include "WeaponController.h"


USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(EnemyController, ala::GameObjectComponent)

EnemyController::EnemyController(ala::GameObject* gameObject, const int health, const std::function<int(WeaponController*)> &damageCalculator, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _maxYDistance(50),
  _startX(0),
  _minX(0),
  _maxX(0),
  _health(health),
  _directionController(NULL),
  _aladdinTransform(NULL),
  _transform(NULL),
  _stateManager(NULL),
  _maxAttackRange(70),
  _resetRange(GameManager::get()->getVisibleWidth() * 0.7f),
  _collidingCharcoalBurner(false),
  _damageCalculator(damageCalculator)
{
}

bool EnemyController::isCollidingCharcoalBurner() const
{
  return _collidingCharcoalBurner;
}

bool EnemyController::willReset() const
{
  return abs(_aladdinTransform->getPositionX() - _transform->getPositionX()) >= _resetRange;
}

bool EnemyController::canSeeAladdin() const
{
  const auto aladdinPosition = _aladdinTransform->getPositionX();

  const auto yDistanceToAladdin = abs(_aladdinTransform->getPositionY() - _transform->getPositionY());
  if(yDistanceToAladdin > _maxYDistance)
  {
    return false;
  }

  if (aladdinPosition >= _minX - _maxAttackRange && aladdinPosition <= _maxX + _maxAttackRange)
  {
    return true;
  }
  return false;
}

bool EnemyController::canAttackAladdin() const
{
  const auto xDistanceToAladdin = abs(_aladdinTransform->getPositionX() - _transform->getPositionX());
  const auto yDistanceToAladdin = abs(_aladdinTransform->getPositionY() - _transform->getPositionY());
  return xDistanceToAladdin <= _maxAttackRange && yDistanceToAladdin <= _maxYDistance;
}

bool EnemyController::canGoLeft() const
{
  return _transform->getPositionX() > _minX;
}

bool EnemyController::canGoRight() const
{
  return _transform->getPositionX() < _maxX;
}

void EnemyController::clampPosition() const
{
  if(_transform->getPositionX() > _maxX)
  {
    _transform->setPositionX(_maxX);
  }

  if (_transform->getPositionX() < _minX)
  {
    _transform->setPositionX(_minX);
  }
}

void EnemyController::updateDirection() const
{
  if (_directionController->getAladdinDirection() < 0)
  {
    _directionController->setLeft();
  }
  else
  {
    _directionController->setRight();
  }
}

float EnemyController::getStartX() const
{
  return _startX;
}

float EnemyController::getMinX() const
{
  return _minX;
}

float EnemyController::getMaxX() const
{
  return _maxX;
}

void EnemyController::setStartX(const float startX)
{
  _startX = startX;
}

void EnemyController::setMinX(const float minX)
{
  _minX = minX;
}

void EnemyController::setMaxX(const float maxX)
{
  _maxX = maxX;
}

float EnemyController::getMaxAttackRange() const
{
  return _maxAttackRange;
}

void EnemyController::setMaxAttackRange(const float maxAttackRange)
{
  _maxAttackRange = maxAttackRange;
}

float EnemyController::getMaxYDistance() const
{
  return _maxYDistance;
}

void EnemyController::setMaxYDistance(const float maxYDistance)
{
  _maxYDistance = maxYDistance;
}

int EnemyController::getHealth() const
{
  return _health;
}

void EnemyController::setHealth(const int health)
{
  _health = health;
}

void EnemyController::onInitialize()
{
  const auto gameManager = GameManager::get();
  const auto gameObject = getGameObject();
  _directionController = gameObject->getComponentT<EnemyDirectionController>();
  _stateManager = gameObject->getComponentT<StateManager>();
  _transform = gameObject->getTransform();
  _aladdinTransform = gameManager->getObjectByTag(ALADDIN_TAG)->getTransform();
  _transform->setPositionX(_startX);
}

void EnemyController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
    ? collision.getColliderB()
    : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
    ? collision.getColliderB()
    : collision.getColliderA();

  if (selfCollider->getTag() == ENEMY_TAG) 
  {
    if ((otherCollider->getTag() == ALADDIN_WEAPON_TAG)) {
      onHit(otherCollider->getGameObject()->getComponentT<WeaponController>());
    }
  }

  if(otherCollider->getTag() == CHARCOAL_BURNER_TAG)
  {
    _collidingCharcoalBurner = true;
  }
}

void EnemyController::onTriggerExit(const ala::CollisionInfo& collision)
{
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
    ? collision.getColliderB()
    : collision.getColliderA();

  if (otherCollider->getTag() == CHARCOAL_BURNER_TAG)
  {
    _collidingCharcoalBurner = false;
  }
}

void EnemyController::onOutOfHealth() const
{
  GameManager::get()->getPrefab("Explosion")->instantiate(_transform->getPosition());
  getGameObject()->release();
}

void EnemyController::onHit(WeaponController* weaponController)
{
  if (_stateManager->getCurrentStateName() == "hit") return;
  
  _stateManager->changeState("hit");

  _health -= _damageCalculator(weaponController);
  if (_health <= 0) 
  {
    onOutOfHealth();
  }

}

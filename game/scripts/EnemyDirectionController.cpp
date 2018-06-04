#include "EnemyDirectionController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(EnemyDirectionController, ala::GameObjectComponent)

EnemyDirectionController::EnemyDirectionController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _directionScalar(-1),
  _transform(NULL),
  _body(NULL),
  _aladdinTransform(NULL)
{
}

EnemyDirectionController::~EnemyDirectionController()
{
}

bool EnemyDirectionController::isLeft() const
{
  return _directionScalar == -1;
}

bool EnemyDirectionController::isRight() const
{
  return _directionScalar == 1;
}

void EnemyDirectionController::setDirectionScalar(const int directionScalar)
{
  _directionScalar = directionScalar;
  _transform->setScaleX(_directionScalar * ABS(_transform->getScale().getX()));

  _body->setVelocity(ala::Vec2(_directionScalar * ABS(_body->getVelocity().getX()), _body->getVelocity().getY()));
}

void EnemyDirectionController::setLeft()
{
  _directionScalar = -1;
  _transform->setScaleX(_directionScalar * ABS(_transform->getScale().getX()));

  _body->setVelocity(ala::Vec2(_directionScalar * ABS(_body->getVelocity().getX()), _body->getVelocity().getY()));
}

void EnemyDirectionController::setRight()
{
  _directionScalar = 1;
  _transform->setScaleX(_directionScalar * ABS(_transform->getScale().getX()));

  _body->setVelocity(ala::Vec2(_directionScalar * ABS(_body->getVelocity().getX()), _body->getVelocity().getY()));
}

void EnemyDirectionController::turn()
{
  _directionScalar = -_directionScalar;
  _transform->setScaleX(_directionScalar * ABS(_transform->getScale().getX()));

  _body->setVelocity(ala::Vec2(_directionScalar * ABS(_body->getVelocity().getX()), _body->getVelocity().getY()));
}

int EnemyDirectionController::getAladdinDirection() const
{
  return _aladdinTransform->getPositionX() - _transform->getPositionX();
}

void EnemyDirectionController::onInitialize()
{
  _transform = getGameObject()->getTransform();
  _transform->setScaleX(_directionScalar * ABS(_transform->getScale().getX()));

  _body = getGameObject()->getComponentT<ala::Rigidbody>();
  _body->setVelocity(ala::Vec2(_directionScalar * ABS(_body->getVelocity().getX()), _body->getVelocity().getY()));

  _aladdinTransform = ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getTransform();
}

#include "ParalaxController.h"
#include "../Macros.h"

/*
* Created by kiennm97 on Oct 15th 2017
*/

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_1(ParalaxController, GameObjectComponent)
  ParalaxController::ParalaxController(ala::GameObject * gameObject, const std::string & name)
  : GameObjectComponent(gameObject, name),
  _speedLayer(5),
  _speedPlayer(0),
  _isStatic(false),
  _startX(0),
  _startY(0)
{
}

void ParalaxController::setIsStatic(const bool isStatic)
{
  _isStatic = isStatic;
}

bool ParalaxController::getIsStatic()
{
  return _isStatic;
}

int ParalaxController::getSpeedPlayer()
{
  return _speedPlayer;
}


void ParalaxController::setSpeedPlayer(const int speedPlayer)
{
  _speedPlayer = speedPlayer;
}


int ParalaxController::getSpeedLayer()
{
  return _speedLayer;
}

void ParalaxController::setSpeedLayer(const int speedLayer)
{
  _speedLayer = speedLayer;
}

void ParalaxController::onInitialize()
{
  //_startX = getGameObject()->getTransform()->getPositionX();
  _startY = getGameObject()->getTransform()->getPositionY();
  getGameObject()->getComponentT<ala::Transform>()->setPositionX(GameManager::get()->getRunningScene()->getMainCamera()->getTransform()->getPositionX()-2000);
}

void ParalaxController::onUpdate(const float delta)
{
  auto layerTransform = getGameObject()->getComponentT<ala::Transform>();
  auto ob = getGameObject()->getComponentT<ala::SpriteRenderer>();
  auto camera = GameManager::get()->getRunningScene()->getMainCamera()->getTransform();

  layerTransform->setPositionY(camera->getPositionY() + _startY);

  if (_isStatic == false)
  {
    layerTransform->setPositionX(layerTransform->getPositionX() - getSpeedLayer() * delta);
    if (layerTransform->getPositionX() <= camera->getPositionX() - ob->getFrameSize().getWidth() / 4)
    {
      getGameObject()->getComponentT<ala::Transform>()->setPositionX(camera->getPositionX() + getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize().getWidth() / 4);
    }
  }

  if (_speedPlayer > 0 && _isStatic == true)
  {
    layerTransform->setPositionX(layerTransform->getPositionX() - getSpeedLayer() * delta);
    if (layerTransform->getPositionX() <= _startX - ob->getFrameSize().getWidth() / 4)
    {
      getGameObject()->getComponentT<ala::Transform>()->setPositionX(_startX + getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize().getWidth() / 4);
    }
  }

  if (_speedPlayer < 0 && _isStatic == true)
  {
    layerTransform->setPositionX(layerTransform->getPositionX() + getSpeedLayer() * delta);
    if (layerTransform->getPositionX() >= _startX + ob->getFrameSize().getWidth() * 3 / 4)
    {
      getGameObject()->getComponentT<ala::Transform>()->setPositionX(_startX + getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize().getWidth() / 4);
    }
  }
}

void ParalaxController::onRelease()
{
}
}

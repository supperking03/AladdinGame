#include "EditorController.h"
#include "input/Input.h"

ALA_CLASS_SOURCE_1(EditorController, GameObjectComponent)

EditorController::EditorController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name), _logger("EditorController")
{
  _currentIndex = 0;
}

EditorController::~EditorController()
{
}

void EditorController::setGameObjects(const std::vector<ala::GameObject*>& gameObjects)
{
  _gameObjects = gameObjects;
}

void EditorController::onInitialize()
{
  _camera = ala::GameManager::get()->getRunningScene()->getMainCamera()->getTransform();
}

void EditorController::onUpdate(const float delta)
{
  if (_gameObjects.size() == 0)
  {
    return;
  }
  if(ala::Input::get()->getKeyDown(ALA_KEY_TAB))
  {
    if(_currentIndex < _gameObjects.size()-1)
    {
      _currentIndex++;
    }
    else
    {
      _currentIndex = 0;
    }
  }

  const auto currentTransform = _gameObjects[_currentIndex]->getTransform();
  _camera->setPosition(currentTransform->getPosition() + ala::Vec2(63,30));

  if (ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW))
  {
    currentTransform->setPosition(currentTransform->getPosition() + ala::Vec2(-3,0));
    //_logger.info("%s %.2f %.2f", currentTransform->getGameObject()->getName(), currentTransform->getPositionX(), currentTransform->getPositionY());
  }
  if (ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW))
  {
    currentTransform->setPosition(currentTransform->getPosition() + ala::Vec2(3, 0));
  }
  if (ala::Input::get()->getKey(ALA_KEY_UP_ARROW))
  {
    currentTransform->setPosition(currentTransform->getPosition() + ala::Vec2(0, 3));
  }
  if (ala::Input::get()->getKey(ALA_KEY_DOWN_ARROW))
  {
    currentTransform->setPosition(currentTransform->getPosition() + ala::Vec2(0, -3));
  }
  if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
  {
    for(auto object: _gameObjects)
    {
      _logger.info("%s %.2f,%.2f", object->getName(), object->getTransform()->getPositionX(), object->getTransform()->getPositionY());
    }
  }
}

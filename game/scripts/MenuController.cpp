#include "MenuController.h"
#include "input/Input.h"
#include "../scenes/AladdinScene.h"
#include "../scenes/DieScene.h"
#include "../Macros.h"
#include "../GameData.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(MenuController, GameObjectComponent)

MenuController::MenuController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name), _logger("MenuController")
{
  _currentIndex = 0;
}

MenuController::~MenuController()
{
}


void MenuController::onInitialize()
{
  getGameObject()->getComponentT<ala::Transform>()->setPosition(-80, -4);
}

void MenuController::onUpdate(const float delta)
{
  if(ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW))
  {
    _currentIndex--;

    switch (_currentIndex % 2)
    {
    case 0:
      getGameObject()->getComponentT<ala::Transform>()->setPosition(getGameObject()->getComponentT<ala::Transform>()->getPositionX(), -4);
      break;
    case 1:
      getGameObject()->getComponentT<ala::Transform>()->setPosition(getGameObject()->getComponentT<ala::Transform>()->getPositionX(), -20);
      break;
    }
  }
  if (ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW))
  {
    _currentIndex++;

    switch (_currentIndex % 2)
    {
    case 0:
      getGameObject()->getComponentT<ala::Transform>()->setPosition(getGameObject()->getComponentT<ala::Transform>()->getPositionX(), -4);
      break;
    case 1:
      getGameObject()->getComponentT<ala::Transform>()->setPosition(getGameObject()->getComponentT<ala::Transform>()->getPositionX(), -20);
      break;
    }
  }
  

  if(ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
  {

    switch (_currentIndex % 2)
    {
    case 0:
      GameData::get()->setInt(SCORE_DATA_KEY, 0);
      GameData::get()->setInt(LIVES_DATA_KEY, 3);
      GameData::get()->setInt(HEALTH_DATA_KEY, 9);
      GameData::get()->setInt(RUBY_DATA_KEY, 0);

      ala::GameManager::get()->getPrefabV2("Aladdin Scene Fade Out Transition")->instantiateWithArgs("AgrabahMarket.tmx");
      break;
    case 1:
      GameData::get()->setInt(SCORE_DATA_KEY, 0);
      GameData::get()->setInt(LIVES_DATA_KEY, 3);
      GameData::get()->setInt(HEALTH_DATA_KEY, 9);
      GameData::get()->setInt(RUBY_DATA_KEY, 0);

      ala::GameManager::get()->getPrefabV2("Aladdin Scene Fade Out Transition")->instantiateWithArgs("JafarBoss.tmx");
      break;
    }
  }
}

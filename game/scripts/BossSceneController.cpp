#include "BossSceneController.h"
#include "../Macros.h"
#include "../arguments/IntArg.h"
#include "../Macros.h"
#include "../GameData.h"
#include "../Macros.h"
#include <debugapi.h>

ALA_CLASS_SOURCE_2(BossSceneController, ala::GameObjectComponent, ala::MessageListener)

BossSceneController::BossSceneController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name), _aladdin(NULL), _jafar(NULL)
{
}

BossSceneController::~BossSceneController()
{
}


void BossSceneController::onInitialize()
{
  _aladdin = ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getTransform();
  _jafar = ala::GameManager::get()->getObjectByName("Jafar")->getTransform();

  _charcoalBurners = ala::GameManager::get()->getObjectByTag(CHARCOAL_BURNER_TAG)->getAllComponentTs<ala::Collider>();

  for (auto i:_charcoalBurners)
  {
    i->setActive(false);
  }

  subscribeGlobalMessage(TURN_ON_CHARCOALBURNER_MESSAGE, [=] (ala::MessageArgs* message)
  {
    OutputDebugString("Hello");
    for (auto i : _charcoalBurners)
    {
      i->setActive(true);
    }
  });
}

void BossSceneController::onUpdate(const float delta)
{
  if (GameData::get()->getInt(APPLE_DATA_KEY) == 0)
  {
    if (_aladdin->getPositionX() > _jafar->getPositionX())
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(SPAWN_APPLE_MESSAGE, new IntArg(2));
    }
    else
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(SPAWN_APPLE_MESSAGE, new IntArg(1));
    }
  }
}



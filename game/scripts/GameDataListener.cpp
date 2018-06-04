#include "GameDataListener.h"
#include "../Macros.h"
#include "../GameData.h"
#include "../arguments/IntArg.h"
#include "../arguments/Vec2Arg.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../scenes/DieScene.h"
#include "../scenes/AladdinScene.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_2(GameDataListener, ala::GameObjectComponent, MessageListener)

GameDataListener::GameDataListener(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name)
{
}

GameDataListener::~GameDataListener()
{
}

void GameDataListener::onInitialize()
{
  subscribeGlobalMessage(APPLE_THROWED_MESSAGE, [=] (ala::MessageArgs* message)
  {
    GameData::get()->setInt(APPLE_DATA_KEY, GameData::get()->getInt(APPLE_DATA_KEY) - 1);
    if(GameData::get()->getInt(APPLE_DATA_KEY) < 0)
    {
      GameData::get()->setInt(APPLE_DATA_KEY, 0);
    }
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(HEALTH_ACQUIRED_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(HEALTH_DATA_KEY, GameData::get()->getInt(HEALTH_DATA_KEY) + payload);
    if (GameData::get()->getInt(HEALTH_DATA_KEY) > 9)
    {
      GameData::get()->setInt(HEALTH_DATA_KEY, 9);
    }
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(HEALTH_LOST_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(HEALTH_DATA_KEY, GameData::get()->getInt(HEALTH_DATA_KEY) - payload);

    if(GameData::get()->getInt(HEALTH_DATA_KEY) < 1)
    {
      const auto currentScene = static_cast<AladdinScene*>(ala::GameManager::get()->getRunningScene());
      ala::GameManager::get()->getPrefabV2("Die Scene Fade Out Transition")->instantiateWithArgs(currentScene->getMapResourceName());
    }
    else
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
    }
  });

  subscribeGlobalMessage(APPLE_ACQUIRED_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(APPLE_DATA_KEY, GameData::get()->getInt(APPLE_DATA_KEY) + payload);
    if (GameData::get()->getInt(APPLE_DATA_KEY) > 99)
    {
      GameData::get()->setInt(APPLE_DATA_KEY, 99);
    }
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(APPLE_STOLEN_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(APPLE_DATA_KEY, GameData::get()->getInt(APPLE_DATA_KEY) - payload);
    if (GameData::get()->getInt(APPLE_DATA_KEY) < 0)
    {
      GameData::get()->setInt(APPLE_DATA_KEY, 0);
    }
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(SCORE_ACQUIRED_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(SCORE_DATA_KEY, GameData::get()->getInt(SCORE_DATA_KEY) + payload);
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(RUBY_ACQUIRED_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(RUBY_DATA_KEY, GameData::get()->getInt(RUBY_DATA_KEY) + payload);
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(RUBY_LOST_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(RUBY_DATA_KEY, GameData::get()->getInt(RUBY_DATA_KEY) - payload);
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(LIVES_ACQUIRED_MESSAGE, [=](ala::MessageArgs* message)
  {
    int payload = static_cast<IntArg*>(message)->getPayload();
    GameData::get()->setInt(LIVES_DATA_KEY, GameData::get()->getInt(LIVES_DATA_KEY) + payload);
    if (GameData::get()->getInt(LIVES_DATA_KEY) > 9)
    {
      GameData::get()->setInt(LIVES_DATA_KEY, 9);
    }
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(CHECKPOINT_CHECKED_MESSAGE, [=](ala::MessageArgs* message)
  {
    auto payload = static_cast<Vec2Arg*>(message)->getPayload();
    GameData::get()->setFloat(CHECKPOINT_DATA_X_KEY, payload.getX());
    GameData::get()->setFloat(CHECKPOINT_DATA_Y_KEY, payload.getY());
    GameData::get()->setString(HAS_CHECKPOINT_KEY, "TRUE");
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(ALADDIN_OUT_OF_HEALTH_MESSAGE, [=](ala::MessageArgs* message)
  {
    GameData::get()->setInt(LIVES_DATA_KEY, GameData::get()->getInt(LIVES_DATA_KEY) - 1);
    ala::GameManager::get()->getGlobalMessenger()->broadcast(UI_CHANGED_MESSAGE, NULL);
  });

  subscribeGlobalMessage(BGM_CHANGED, [=](ala::MessageArgs* message)
  {
    auto payload = static_cast<ala::StringMessageArgs*>(message)->getPayload();
    GameData::get()->setString(BGM_KEY, payload);
    ala::GameManager::get()->getGlobalMessenger()->broadcast(payload == "ON"? RESUME_BACKGROUND_MESSAGE: STOP_BACKGROUND_MESSAGE, NULL);
  });

  subscribeGlobalMessage(SFX_CHANGED, [=](ala::MessageArgs* message)
  {
    auto payload = static_cast<ala::StringMessageArgs*>(message)->getPayload();
    GameData::get()->setString(SFX_KEY, payload);
  });

  subscribeGlobalMessage(DIFFICULTY_CHANGED, [=](ala::MessageArgs* message)
  {
    auto payload = static_cast<ala::StringMessageArgs*>(message)->getPayload();
    GameData::get()->setString(DIFFICULTY_KEY, payload);
  });
}

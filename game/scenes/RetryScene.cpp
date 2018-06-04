/*
*
*/

#include "RetryScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/GameDataListener.h"
#include "../Macros.h"
#include "../GameData.h"
#include "AladdinScene.h"
#include "MenuScene.h"
#include "../scripts/AladdinController.h"
#include "../Macros.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

RetryScene::RetryScene(const std::string& lastMap)
{
  _lastMap = lastMap;
}

void RetryScene::onPreInitialize() {
  const auto gameManager = GameManager::get();
  gameManager->getPrefab("Fade In Effect")->instantiate();
  auto victory_img = new GameObject(this, "retry");
  auto sr0 = new ala::SpriteRenderer(victory_img, "retry.png");
  victory_img->getTransform()->setPosition(0, 0);

  auto abu = new GameObject(this, "abu");
  new ala::SpriteRenderer(abu, "abu.png");
  const auto animatorAbu = new ala::Animator(abu, "abu-retry", "abu.anm");
  const auto stateManagerAbu = new ala::StateManager(abu, "abu-stand");
  const auto idleTimerAbu = new ala::Timer(abu);

  auto aladdin = new GameObject(this, "aladdin");
  new ala::SpriteRenderer(aladdin, "aladdin.png");
  const auto animator = new ala::Animator(aladdin, "idle1", "aladdin.anm");
  const auto stateManager = new ala::StateManager(aladdin, "stand");
  const auto idleTimer = new ala::Timer(aladdin);


  abu->getTransform()->setPosition(15, -70);
  aladdin->getTransform()->setPosition(-12, -70);

  new ala::State(stateManagerAbu, "abu-stand",
    [=] {
    animatorAbu->setAction("abu-retry");
  },
    [=](float delta) {
    if (animatorAbu->getAction()->getActionName() == "abu-retry" && !animatorAbu->isPlaying() && idleTimerAbu->isDone())
    {
      animatorAbu->setAction("abu-retry2");
      idleTimerAbu->start(1.0f * (400 + rand() % 900) / 1000);
      return;
    }

    if (animatorAbu->getAction()->getActionName() == "abu-retry2" && !animatorAbu->isPlaying() && idleTimerAbu->isDone())
    {
      animatorAbu->setAction("abu-retry");
      idleTimerAbu->start(1.0f * (800 + rand() % 900) / 1000);
      return;
    }
  },
    NULL);

  new ala::State(stateManagerAbu, "abu-run",
    [=] {
    animatorAbu->setAction("abu-run");
  }, [=](float dt)
  {
    abu->getTransform()->setPositionX(aladdin->getTransform()->getPositionX() + 27);
  }, NULL);


  
  new ala::State(stateManager, "stand",
    [=] {
    animator->setAction("idle1");
  },
    [=](float delta) {
    if (animator->getAction()->getActionName() == "idle1" && !animator->isPlaying() && idleTimer->isDone())
    {
      animator->setAction("idle2");
      idleTimer->start(1.0f * (400 + rand() % 900) / 1000);
      return;
    }

    if (animator->getAction()->getActionName() == "idle2" && !animator->isPlaying() && idleTimer->isDone())
    {
      animator->setAction("idle1");
      idleTimer->start(1.0f * (800 + rand() % 900) / 1000);
      return;
    }
  },
    NULL);

  new ala::State(stateManager, "aladdin-run-left",
    [=] {
    animator->setAction("run2");
    aladdin->getTransform()->setScaleX(-1);
  }, [=](float dt)
  {
    aladdin->getTransform()->setPositionX(aladdin->getTransform()->getPositionX() - 3);
  }, NULL);

  new ala::State(stateManager, "aladdin-run-right",
    [=] {
    animator->setAction("run2");
    abu->getTransform()->setScaleX(-1);
  }, [=](float dt)
  {
    aladdin->getTransform()->setPositionX(aladdin->getTransform()->getPositionX() + 3);
  }, NULL);


  new ala::StateTransition(stateManager, "stand", "aladdin-run-left", [=] {
    return ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW);
  });

  new ala::StateTransition(stateManager, "stand", "aladdin-run-right", [=] {
    return ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW);
  });

  new ala::StateTransition(stateManagerAbu, "abu-stand", "abu-run", [=] {
    return ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW) || ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW);
  });

  //GameData::get()->setInt(APPLE_DATA_KEY, 10);

  const auto gameDataListener = new GameObject(this, "Game Data Listener");
  new GameDataListener(gameDataListener);

  ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("LevelComplete.wav"));

}

void RetryScene::onPostUpdate(const float delta)
{
  if (GameManager::get()->getObjectByName("aladdin")->getTransform()->getPositionX() <= -200)
  {
    GameManager::get()->replaceScene(new MenuScene);
  }
  if (GameManager::get()->getObjectByName("aladdin")->getTransform()->getPositionX() >= 200)
  {
    if (GameData::get()->getString(DIFFICULTY_KEY) == "EASY")
    {
      GameData::get()->setInt(SCORE_DATA_KEY, 0);
      GameData::get()->setInt(LIVES_DATA_KEY, 3);
      GameData::get()->setInt(HEALTH_DATA_KEY, 9);
      GameData::get()->setInt(RUBY_DATA_KEY, 0);
      GameData::get()->setInt(APPLE_DATA_KEY, 10);
      GameData::get()->setString(HAS_CHECKPOINT_KEY, "FALSE");
    }
    else
    {
      GameData::get()->setInt(SCORE_DATA_KEY, 0);
      GameData::get()->setInt(LIVES_DATA_KEY, 2);
      GameData::get()->setInt(HEALTH_DATA_KEY, 7);
      GameData::get()->setInt(RUBY_DATA_KEY, 0);
      GameData::get()->setInt(APPLE_DATA_KEY, 8);
      GameData::get()->setString(HAS_CHECKPOINT_KEY, "FALSE");
    }
    ala::GameManager::get()->getPrefabV2("Aladdin Scene Fade Out Transition")->instantiateWithArgs(_lastMap);
  }
}

void RetryScene::onPreRelease() {}

void RetryScene::onPostInitialize()
{
  
}

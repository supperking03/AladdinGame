/*
*
*/

#include "DieScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/GameDataListener.h"
#include "../Macros.h"
#include "../GameData.h"
#include "AladdinScene.h"
#include "RetryScene.h"

USING_NAMESPACE_ALA;

DieScene::DieScene(const std::string& lastMap)
{
  _lastMap = lastMap;
}

void DieScene::onPreInitialize() {
  GameManager::get()->getPrefab("Fade In Effect")->instantiate();
  const auto aladdin_die = new GameObject(this, "aladdin_die");
  new ala::SpriteRenderer(aladdin_die, "aladdin.png");
  const auto animator = new ala::Animator(aladdin_die, "game-over", "aladdin.anm");
  auto stateManager = new StateManager(aladdin_die, "die");

  new State(stateManager, "die", NULL, [=] (float delta)
  {
    if (!animator->isPlaying())
    {
      if(GameData::get()->getInt(LIVES_DATA_KEY) <= 0)
      {
        ala::GameManager::get()->getPrefabV2("Retry Scene Fade Out Transition")->instantiateWithArgs(_lastMap);
      }
      else
      {
        GameData::get()->setInt(HEALTH_DATA_KEY, 9);
        GameData::get()->setInt(APPLE_DATA_KEY, 10);
        GameData::get()->setInt(LIVES_DATA_KEY, GameData::get()->getInt(LIVES_DATA_KEY) - 1);
        ala::GameManager::get()->getPrefabV2("Aladdin Scene Fade Out Transition")->instantiateWithArgs(_lastMap);
      }
    }
  }, NULL);

  auto abu_end = new GameObject(this, "abu_end");
  new ala::SpriteRenderer(abu_end, "abu_end.png");
  new ala::Animator(abu_end, "abu_end", "aladdin.anm");
  abu_end->getTransform()->setPosition(80, -20);

  const auto gameDataListener = new GameObject(this, "Game Data Listener");
  new GameDataListener(gameDataListener);
}

void DieScene::onPreRelease() {}

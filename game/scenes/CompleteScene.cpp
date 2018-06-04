/*
*
*/

#include "CompleteScene.h"
#include "../scripts/CameraController.h"
#include "../scripts/GameDataListener.h"
#include "../Macros.h"
#include "../GameData.h"
#include "AladdinScene.h"
#include "MenuScene.h"

USING_NAMESPACE_ALA;

CompleteScene::CompleteScene() {}

void CompleteScene::onPreInitialize() {
  GameManager::get()->getPrefab("Fade In Effect")->instantiate();
  GameManager::get()->getPrefab("Audio Event Listener")->instantiate();

  const auto gameManager = GameManager::get();
  enablePhysics(Vec2(0, -1000.f));

  auto victory_img = new GameObject(this, "victory");
  auto sr0 = new ala::SpriteRenderer(victory_img, "victory.png");
  victory_img->getTransform()->setPosition(0, 0);

  auto aladdin_victory = new GameObject(this, "aladdin_victory");
  auto sr1 = new ala::SpriteRenderer(aladdin_victory, "aladdin.png");
  const auto animator = new ala::Animator(aladdin_victory, "stage-completed", "aladdin.anm");
  aladdin_victory->getTransform()->setPosition(300, -70);

  auto actionManager1 = new ala::ActionManager(aladdin_victory);
  auto moveBy1 = new ala::MoveBy(ala::Vec2(-800, 0), 6);
  actionManager1->addAction(moveBy1);

  auto abu_victory = new GameObject(this, "abu_victory");
  auto sr2 = new ala::SpriteRenderer(abu_victory, "abu_victory.png");
  const auto animator1 = new ala::Animator(abu_victory, "abu_victory", "aladdin.anm");
  abu_victory->getTransform()->setPosition(250, -70);

  auto actionManager2 = new ala::ActionManager(abu_victory);
  auto moveBy2 = new ala::MoveBy(ala::Vec2(-800, 0), 6);
  actionManager2->addAction(moveBy2);

  //GameData::get()->setInt(APPLE_DATA_KEY, 10);

  const auto gameDataListener = new GameObject(this, "Game Data Listener");
  new GameDataListener(gameDataListener);

  ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("LevelComplete.wav"));

}

void CompleteScene::onPostUpdate(const float delta)
{
  if (GameManager::get()->getObjectByName("aladdin_victory")->getTransform()->getPositionX() <=-200)
  {
    GameManager::get()->replaceScene(new MenuScene);
  }
}

void CompleteScene::onPreRelease() {}

void CompleteScene::onPostInitialize()
{
  GameManager::get()->getGlobalMessenger()->broadcast(PLAY_BACKGROUND_MESSAGE, new StringMessageArgs("LevelComplete.wav"));
}

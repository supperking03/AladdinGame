#include "MenuScene.h"\

#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../scripts/GameDataListener.h"
USING_NAMESPACE_ALA;

MenuScene::MenuScene(){}

void MenuScene::onPreInitialize() {
  const auto gameManager = GameManager::get();
  gameManager->getPrefab("Fade In Effect")->instantiate();
  const auto background = new GameObject(this);
  background->setTag(BACKGROUND_TAG);
  new SpriteRenderer(background, "cutscenes.png");
  new Animator(background, "cutscene_1", "cutscenes.anm");
  background->setLayer("Background");
  background->getTransform()->setPosition(0, 0);

  const auto aladdinLogo = new GameObject(this);
  new SpriteRenderer(aladdinLogo, "aladdinPoster.png");
  aladdinLogo->getTransform()->setPositionY(70);
  aladdinLogo->setLayer("UI");

  //const auto rainbowLabel = new ala::GameObject(this);
  //const auto rainbowLabelText = new ala::BitmapText(rainbowLabel, "font_one.png", "one.fnt");
  //rainbowLabel->getTransform()->setPosition(ala::Vec2(0, -gameManager->getVisibleHeight() / 2 + 50));
  //rainbowLabelText->setTextAlignment(ala::BitmapText::CENTER);
  //rainbowLabelText->setCharacterSpacing(0);
  //rainbowLabelText->setText("TEAM RAINBOW !");

  const auto segaLabel = new ala::GameObject(this);
  const auto segaLabelText = new ala::BitmapText(segaLabel, "font_one.png", "one.fnt");
  segaLabel->getTransform()->setPosition(ala::Vec2(0, -gameManager->getVisibleHeight()/2 + 30));
  segaLabelText->setTextAlignment(ala::BitmapText::CENTER);
  segaLabelText->setCharacterSpacing(0);
  segaLabelText->setText("(C) 1993 SEGA. (C) 1993 VIRGIN GAMES");

  const auto disneyLabel = new ala::GameObject(this);
  const auto disneyLabelText = new ala::BitmapText(disneyLabel, "font_one.png", "one.fnt");
  disneyLabel->getTransform()->setPosition(ala::Vec2(0, -gameManager->getVisibleHeight() / 2 + 10));
  disneyLabelText->setTextAlignment(ala::BitmapText::CENTER);
  disneyLabelText->setCharacterSpacing(0);
  disneyLabelText->setText("(C) 1993 THE WALT DISNEY COMPANY");

  gameManager->getPrefab("Play Menu")->instantiate("Play Menu");

  subscribeGlobalMessage(OPEN_PLAY_SCENE_MESSAGE, [=](MessageArgs* message)
  {
    GameManager::get()->getObjectByName("Option Menu")->release();
    gameManager->getPrefab("Play Menu")->instantiate("Play Menu");
  });

  subscribeGlobalMessage(OPEN_OPTION_SCENE_MESSAGE, [=](MessageArgs* message)
  {
    GameManager::get()->getObjectByName("Play Menu")->release();
    gameManager->getPrefab("Option Menu")->instantiate("Option Menu");
  });

  const auto gameListeners = new GameObject(this, "Game Listeners");
  new GameDataListener(gameListeners);
  GameManager::get()->getPrefab("Audio Event Listener")->instantiate();
}

void MenuScene::onPostInitialize()
{
  GameManager::get()->getGlobalMessenger()->broadcast(PLAY_BACKGROUND_MESSAGE, new StringMessageArgs("AWholeNewWorld.wav"));
}

void MenuScene::onPreRelease() {}

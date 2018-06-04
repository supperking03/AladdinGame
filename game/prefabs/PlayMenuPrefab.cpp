#include "PlayMenuPrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "audio/AudioSource.h"
#include "2d/BitmapText.h"
#include "input/Input.h"
#include "../scenes/AladdinScene.h"
#include "../Macros.h"
#include "../GameData.h"
#include "../Macros.h"
#include "../Macros.h"

void PlayMenuPrefab::doInstantiate(ala::GameObject* object) const
{
  const auto menuSelector = new ala::GameObject(object);
  new ala::SpriteRenderer(menuSelector, "items.png");
  new ala::Animator(menuSelector, "menu_select", "items.anm");
  menuSelector->getTransform()->setPosition(-95, 0);

  auto actionManager = new ala::ActionManager(menuSelector);
  const auto moveBy = new ala::MoveBy(ala::Vec2(15, 0), 0.3);
  const auto revert = new ala::MoveBy(ala::Vec2(-15, 0), 0.3);

  vector<ala::Action*> actions;
  actions.push_back(moveBy);
  actions.push_back(revert);
  const auto sequence = new ala::Sequence(actions);
  const auto repeat = new ala::Repeat(sequence, -1);
  actionManager->addAction(repeat);


  const auto agrabahMarketLabel = new ala::GameObject(object);
  const auto agrabahMarketLabelText = new ala::BitmapText(agrabahMarketLabel, "font_one.png", "one.fnt");
  agrabahMarketLabel->getTransform()->setPosition(ala::Vec2(-60, 0));
  agrabahMarketLabelText->setTextAlignment(ala::BitmapText::LEFT);
  agrabahMarketLabelText->setCharacterSpacing(2);
  agrabahMarketLabelText->setText("AGRABAH MARKET");

  const auto bossLabel = new ala::GameObject(object);
  const auto bossLabelText = new ala::BitmapText(bossLabel, "font_one.png", "one.fnt");
  bossLabel->getTransform()->setPosition(ala::Vec2(-60, -20));
  bossLabelText->setTextAlignment(ala::BitmapText::LEFT);
  bossLabelText->setCharacterSpacing(2);
  bossLabelText->setText("BOSS");

  const auto optionLabel = new ala::GameObject(object);
  const auto optionLabelText = new ala::BitmapText(optionLabel, "font_one.png", "one.fnt");
  optionLabel->getTransform()->setPosition(ala::Vec2(-60, -40));
  optionLabelText->setTextAlignment(ala::BitmapText::LEFT);
  optionLabelText->setCharacterSpacing(2);
  optionLabelText->setText("OPTION");

  const auto stateManager = new ala::StateManager(object, "agrabah-market");

  new ala::State(stateManager, "agrabah-market",
    [=] {
    menuSelector->getTransform()->setPositionY(0);
  },
    [=](float delta) {
    if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
    {
      if(GameData::get()->getString(DIFFICULTY_KEY) == "EASY")
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


      ala::GameManager::get()->replaceScene(new AladdinScene("AgrabahMarket.tmx"));
    }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::State(stateManager, "boss",
    [=] {
    menuSelector->getTransform()->setPositionY(-20);
  },
    [=](float delta) {
    if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
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
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuSelect.wav"));
      ala::GameManager::get()->replaceScene(new AladdinScene("JafarBoss.tmx"));
    }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::State(stateManager, "option",
    [=] {
    menuSelector->getTransform()->setPositionY(-40);
  },
    [=](float delta) {
    if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuSelect.wav"));
      ala::GameManager::get()->getGlobalMessenger()->broadcast(OPEN_OPTION_SCENE_MESSAGE, NULL);
    }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::StateTransition(stateManager, "agrabah-market", "boss", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "boss", "agrabah-market", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "boss", "option", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "option", "boss", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "option", "agrabah-market", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "agrabah-market", "option", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
}

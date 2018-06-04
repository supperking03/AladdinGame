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
#include "OptionMenuPrefab.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"

void OptionMenuPrefab::doInstantiate(ala::GameObject* object) const
{
  const auto menuSelector = new ala::GameObject(object);
  new ala::SpriteRenderer(menuSelector, "items.png");
  new ala::Animator(menuSelector, "menu_select", "items.anm");
  menuSelector->getTransform()->setPosition(-135, 0);

  auto actionManager = new ala::ActionManager(menuSelector);
  const auto moveBy = new ala::MoveBy(ala::Vec2(15, 0), 0.3);
  const auto revert = new ala::MoveBy(ala::Vec2(-15, 0), 0.3);

  vector<ala::Action*> actions;
  actions.push_back(moveBy);
  actions.push_back(revert);
  const auto sequence = new ala::Sequence(actions);
  const auto repeat = new ala::Repeat(sequence, -1);
  actionManager->addAction(repeat);


  const auto sfxSoundLabel = new ala::GameObject(object);
  const auto  sfxSoundLabelText = new ala::BitmapText(sfxSoundLabel, "font_one.png", "one.fnt");
  sfxSoundLabel->getTransform()->setPosition(ala::Vec2(-100, 0));
  sfxSoundLabelText->setTextAlignment(ala::BitmapText::LEFT);
  sfxSoundLabelText->setCharacterSpacing(2);
  sfxSoundLabelText->setText(GameData::get()->getString(SFX_KEY) == "ON" ? "PLAY SFX: ON": "PLAY SFX: OFF");

  const auto backgoundSoundLabel = new ala::GameObject(object);
  const auto backgroundSoundLabelText = new ala::BitmapText(backgoundSoundLabel, "font_one.png", "one.fnt");
  backgoundSoundLabel->getTransform()->setPosition(ala::Vec2(-100, -20));
  backgroundSoundLabelText->setTextAlignment(ala::BitmapText::LEFT);
  backgroundSoundLabelText->setCharacterSpacing(2);
  backgroundSoundLabelText->setText(GameData::get()->getString(BGM_KEY) == "ON"?"PLAY BACKGROUND: ON": "PLAY BACKGROUND: OFF");

  const auto difficultLabel = new ala::GameObject(object);
  const auto difficultLabelText = new ala::BitmapText(difficultLabel, "font_one.png", "one.fnt");
  difficultLabel->getTransform()->setPosition(ala::Vec2(-100, -40));
  difficultLabelText->setTextAlignment(ala::BitmapText::LEFT);
  difficultLabelText->setCharacterSpacing(2);
  difficultLabelText->setText(GameData::get()->getString(DIFFICULTY_KEY) == "EASY" ? "DIFFICULTY: EASY" : "DIFFICULTY: HARD");


  const auto backLabel = new ala::GameObject(object);
  const auto backLabelText = new ala::BitmapText(backLabel, "font_one.png", "one.fnt");
  backLabel->getTransform()->setPosition(ala::Vec2(-100, -60));
  backLabelText->setTextAlignment(ala::BitmapText::LEFT);
  backLabelText->setCharacterSpacing(2);
  backLabelText->setText("BACK");

  const auto stateManager = new ala::StateManager(object, "sfx");

  new ala::State(stateManager, "sfx",
    [=] {
    menuSelector->getTransform()->setPositionY(0);
  },
    [=](float delta) {
      if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
      {
        ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuSelect.wav"));
        if (sfxSoundLabelText->getText() == "PLAY SFX: ON")
        {
          sfxSoundLabelText->setText("PLAY SFX: OFF");
          ala::GameManager::get()->getGlobalMessenger()->broadcast(SFX_CHANGED, new ala::StringMessageArgs("OFF"));
        }
        else
        {
          sfxSoundLabelText->setText("PLAY SFX: ON");
          ala::GameManager::get()->getGlobalMessenger()->broadcast(SFX_CHANGED, new ala::StringMessageArgs("ON"));
        }
      }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::State(stateManager, "background",
    [=] {
    menuSelector->getTransform()->setPositionY(-20);
  },
    [=](float delta) {
    if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuSelect.wav"));
      if (backgroundSoundLabelText->getText() == "PLAY BACKGROUND: ON")
      {
        backgroundSoundLabelText->setText("PLAY BACKGROUND: OFF");
        ala::GameManager::get()->getGlobalMessenger()->broadcast(BGM_CHANGED, new ala::StringMessageArgs("OFF"));
      }
      else
      {
        backgroundSoundLabelText->setText("PLAY BACKGROUND: ON");
        ala::GameManager::get()->getGlobalMessenger()->broadcast(BGM_CHANGED, new ala::StringMessageArgs("ON"));
      }
    }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::State(stateManager, "difficulty",
    [=] {
    menuSelector->getTransform()->setPositionY(-40);
  },
    [=](float delta) {
    if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuSelect.wav"));
      if(difficultLabelText->getText() == "DIFFICULTY: EASY")
      {
        difficultLabelText->setText("DIFFICULTY: HARD");
        ala::GameManager::get()->getGlobalMessenger()->broadcast(DIFFICULTY_CHANGED, new ala::StringMessageArgs("HARD"));
      }
      else
      {
        difficultLabelText->setText("DIFFICULTY: EASY");
        ala::GameManager::get()->getGlobalMessenger()->broadcast(DIFFICULTY_CHANGED, new ala::StringMessageArgs("EASY"));
      }
    }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::State(stateManager, "back",
    [=] {
    menuSelector->getTransform()->setPositionY(-60);
  },
    [=](float delta) {
    if (ala::Input::get()->getKeyDown(ALA_KEY_RETURN))
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuSelect.wav"));
      ala::GameManager::get()->getGlobalMessenger()->broadcast(OPEN_PLAY_SCENE_MESSAGE, NULL);
    }
  },
    [=]()
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("MenuChange.wav"));
  });

  new ala::StateTransition(stateManager, "background", "sfx", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "sfx", "background", []{
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "background", "difficulty", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "difficulty", "background", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "difficulty", "back", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "back", "difficulty", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "sfx", "back", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "back", "sfx", [] {
    return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
}

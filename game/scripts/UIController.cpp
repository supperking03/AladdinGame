#include "UIController.h"
#include "../Macros.h"
#include "../GameData.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_2(UIController, ala::GameObjectComponent, ala::MessageListener)

UIController::UIController(ala::GameObject* gameObject, ala::BitmapText* livesText, ala::BitmapText* scoreText, ala::BitmapText* applesText, ala::BitmapText* rubyText, ala::SpriteRenderer* aladdinHead, ala::SpriteRenderer* applesSprite, ala::SpriteRenderer* rubySprite, ala::Animator* healthAnimator, ala::ActionManager* healthActionManager, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _livesText(livesText),
  _scoreText(scoreText),
  _applesText(applesText),
  _rubyText(rubyText),
  _aladdinHead(aladdinHead),
  _applesSprite(applesSprite),
  _rubySprite(rubySprite),
  _healthAnimator(healthAnimator),
  _healthActionManager(healthActionManager)
{
}

UIController::~UIController()
{
}

void UIController::onInitialize()
{
  subscribeGlobalMessage(UI_CHANGED_MESSAGE, [=](ala::MessageArgs* message) {
    updateUI();
  });
  updateUI();
}

void UIController::updateUI() const
{
  auto gameData = GameData::get();
  const auto health = gameData->getInt(HEALTH_DATA_KEY);
  const auto score = gameData->getInt(SCORE_DATA_KEY);
  const auto apples = gameData->getInt(APPLE_DATA_KEY);
  const auto lives = gameData->getInt(LIVES_DATA_KEY);
  const auto ruby = gameData->getInt(RUBY_DATA_KEY);

  if (apples <= 0)
  {
    _applesText->setVisible(false);
    _applesSprite->setVisible(false);
  }
  else
  {
    _applesText->setVisible(true);
    _applesSprite->setVisible(true);
    _applesText->setText(to_string(apples));

    if(apples <= 5&& apples > 0)
    {
      _applesSprite->getGameObject()->getComponentT<ala::ActionManager>()->addAction(new ala::Blink(0.2, -1));
    }
    else
    {
      _applesSprite->getGameObject()->getComponentT<ala::ActionManager>()->stopAll();
    }
  }

  _livesText->setText(to_string(lives));

  if(score <= 0)
  {
    _scoreText->setVisible(false);
  }
  else
  {
    _scoreText->setVisible(true);
    _scoreText->setText(to_string(score));
  }

  if(ruby <= 0)
  {
    _rubyText->setVisible(false);
    _rubySprite->setVisible(false);
  }
  else
  {
    _rubyText->setVisible(true);
    _rubySprite->setVisible(true);
    _rubyText->setText(to_string(ruby));
  }

  _healthAnimator->setAction("health_bar_" + std::to_string(health));
  if(health == 1)
  {
    _healthActionManager->addAction(new ala::Blink(0.1, -1));
  }
  else
  {
    _healthActionManager->stopAll();
  }
}

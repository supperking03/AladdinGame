#include "UIPrefab.h"
#include "../scripts/UIController.h"

void UIPrefab::doInstantiate(ala::GameObject* object) const
{
  const auto gameManager = ala::GameManager::get();
  const auto visibleWidth = gameManager->getVisibleWidth();
  const auto visibleHeight = gameManager->getVisibleHeight();
  const auto halfVisibleWidth = visibleWidth / 2;
  const auto halfVisibleHeight = visibleHeight / 2;

  // components
  const auto aladdinHead = new ala::GameObject(object);
  const auto aladdinHeadSprite = new ala::SpriteRenderer(aladdinHead, "items.png");
  new ala::Animator(aladdinHead, "aladdin_head", "items.anm");
  aladdinHead->getTransform()->setPosition(ala::Vec2(-halfVisibleWidth + 20, -halfVisibleHeight + 20));

  const auto livesLabel = new ala::GameObject(object);
  const auto livesLabelText = new ala::BitmapText(livesLabel, "font_two.png", "two.fnt");
  livesLabel->getTransform()->setPosition(ala::Vec2(aladdinHead->getTransform()->getPositionX() + 17, -halfVisibleHeight + 17));
  livesLabelText->setTextAlignment(ala::BitmapText::LEFT);
  livesLabelText->setText("99");

  const auto apples = new ala::GameObject(object);
  const auto applesSprite = new ala::SpriteRenderer(apples, "items.png");
  new ala::ActionManager(apples);
  new ala::Animator(apples, "apple", "items.anm");
  apples->getTransform()->setScale(1.5f);
  apples->getTransform()->setPosition(ala::Vec2(halfVisibleWidth - 55, -halfVisibleHeight + 20));

  const auto applesLabel = new ala::GameObject(object);
  const auto applesLabelText = new ala::BitmapText(applesLabel, "font_two.png", "two.fnt");
  applesLabel->getTransform()->setPosition(ala::Vec2(apples->getTransform()->getPositionX() + 13, -halfVisibleHeight + 18));
  applesLabelText->setTextAlignment(ala::BitmapText::LEFT);
  applesLabelText->setText("99");

  const auto ruby = new ala::GameObject(object);
  const auto rubySprite = new ala::SpriteRenderer(ruby, "ruby.png");
  
  ruby->getTransform()->setPosition(ala::Vec2(halfVisibleWidth - 105, -halfVisibleHeight + 20));

  const auto rubyLabel = new ala::GameObject(object);
  const auto rubyLabelText = new ala::BitmapText(rubyLabel, "font_two.png", "two.fnt");
  rubyLabel->getTransform()->setPosition(ala::Vec2(ruby->getTransform()->getPositionX() + 13, -halfVisibleHeight + 18));
  rubyLabelText->setTextAlignment(ala::BitmapText::LEFT);
  rubyLabelText->setText("99");

  const auto scoresLabel = new ala::GameObject(object);
  const auto scoresLabelText = new ala::BitmapText(scoresLabel, "font_one.png", "one.fnt");
  scoresLabel->getTransform()->setPosition(ala::Vec2(halfVisibleWidth - 15, halfVisibleHeight - 20));
  scoresLabelText->setTextAlignment(ala::BitmapText::RIGHT);
  scoresLabelText->setCharacterSpacing(2);
  scoresLabelText->setText("9999");

  const auto health = new ala::GameObject(object);
  new ala::SpriteRenderer(health, "items.png");
  const auto healthAnimator = new ala::Animator(health, "health_bar_9", "items.anm");
  const auto healthTransform = health->getTransform();
  healthTransform->setScale(0.4);
  healthTransform->setPosition(ala::Vec2(-90, 85));
  const auto actionManager = new ala::ActionManager(health);

  new UIController(object, livesLabelText, scoresLabelText, applesLabelText, rubyLabelText, aladdinHeadSprite, applesSprite, rubySprite, healthAnimator, actionManager);

  object->setLayer("UI");
  
}

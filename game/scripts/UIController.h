#ifndef __UI_CONTROLLER_H__
#define __UI_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_2(UIController, ala::GameObjectComponent, ala::MessageListener)
private:
  ala::BitmapText* _livesText;
  ala::BitmapText* _scoreText;
  ala::BitmapText* _applesText;
  ala::BitmapText* _rubyText;

  ala::SpriteRenderer* _aladdinHead;
  ala::SpriteRenderer* _applesSprite;
  ala::SpriteRenderer* _rubySprite;
  ala::Animator* _healthAnimator;

  ala::ActionManager* _healthActionManager;
public:
  UIController(ala::GameObject* gameObject, ala::BitmapText* livesText, ala::BitmapText* scoreText, ala::BitmapText* applesText, ala::BitmapText* rubyText, ala::SpriteRenderer* aladdinHead, ala::SpriteRenderer* applesSprite, ala::SpriteRenderer* rubySprite,ala::Animator* healthAnimator, ala::ActionManager* healthActionManager,const std::string& name = "");
  virtual ~UIController();

  void onInitialize() override;

private:
  void updateUI() const;
};

#endif __UI_CONTROLLER_H__
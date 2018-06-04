#ifndef __FADE_IN_EFFECT_H__
#define __FADE_IN_EFFECT_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FadeInEffect, ala::GameObjectComponent)
private:
  bool _running;
  float _speed;

  std::vector<ala::RectRenderer*> _rectRenderers;
  std::vector<ala::SpriteRenderer*> _spriteRenderers;

public:
  FadeInEffect(ala::GameObject* gameObject, const std::string& name = "");

  void start(const float duration);

  bool isRunning() const;

protected:
  void onInitialize() override;

  void onUpdate(const float delta) override;
};

#endif //!__FADE_IN_EFFECT_H__
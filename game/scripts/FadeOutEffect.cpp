#include "FadeOutEffect.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(FadeOutEffect, ala::GameObjectComponent)

FadeOutEffect::FadeOutEffect(ala::GameObject* gameObject, const std::string& name) :
  GameObjectComponent(gameObject, name), _running(false), _speed(0) {}

void FadeOutEffect::start(const float duration) {
  _speed = 1.0f / duration;
  _running = true;
}

bool FadeOutEffect::isRunning() const {
  return _running;
}

void FadeOutEffect::onInitialize() {
  for (auto spriteRenderer : getGameObject()->getAllComponentTs<SpriteRenderer>()) {
    _spriteRenderers.push_back(spriteRenderer);
  }
  for (auto rectRenderer : getGameObject()->getAllComponentTs<RectRenderer>()) {
    _rectRenderers.push_back(rectRenderer);
  }
}

void FadeOutEffect::onUpdate(const float delta) {
  if (!_running) return;

  _running = false;

  const auto deltaOpacity = _speed * delta;

  for (auto rectRenderer : _rectRenderers) {
    const auto newOpacity = rectRenderer->getOpacity() - deltaOpacity;
    if (newOpacity > 0) {
      _running = true;
      rectRenderer->setOpacity(newOpacity);
    }
    else {
      rectRenderer->setOpacity(0);
    }
  }
  for (auto spriteRenderer : _spriteRenderers) {
    const auto opacity = MIN(1.0f, MAX(0, spriteRenderer->getBackColor().getA() / 255.0f));
    const auto newOpacity = opacity - deltaOpacity;

    if (newOpacity > 0) {
      _running = true;
      spriteRenderer->setBackColor(
        Color(spriteRenderer->getBackColor().getR(),
          spriteRenderer->getBackColor().getG(),
          spriteRenderer->getBackColor().getB(),
          static_cast<unsigned char>(newOpacity * 255)
        ));
    }
    else {
      spriteRenderer->setBackColor(
        Color(spriteRenderer->getBackColor().getR(),
          spriteRenderer->getBackColor().getG(),
          spriteRenderer->getBackColor().getB(),
          0
        ));
    }

  }
}
#include "DynamicParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DynamicParallaxController, ala::GameObjectComponent)

DynamicParallaxController::DynamicParallaxController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _coef(0.1f), _movingSpeed(10.0f), _selfTransform(NULL) {}

void DynamicParallaxController::setOffset(const ala::Vec2& offset) {
  _offset = offset;
}

void DynamicParallaxController::setCoef(const float speed) {
  _coef = speed;
}

void DynamicParallaxController::setMovingSpeed(const float speed) {
  _movingSpeed = speed;
}

void DynamicParallaxController::onInitialize() {
  _selfTransform = getGameObject()->getTransform();

  const auto& transformChildren = _selfTransform->getChildren();
  for (size_t i = 0; i < transformChildren.size() - 1; i += 2) {
    const auto transformChildR = transformChildren[i];
    const auto transformChildL = transformChildren[i + 1];

    _layerTransforms.push_back(transformChildR);
    _layerTransforms.push_back(transformChildL);
    _layerSizes.push_back(transformChildR->getGameObject()->getComponentT<SpriteRenderer>()
      ->getFrameSize().getWidth());
    _layerMovingOffset.push_back(0);
  }
}

void DynamicParallaxController::onRender() {
  const auto gameManager = GameManager::get();
  const auto camera = gameManager->getRunningScene()->getMainCamera();
  const auto cameraPosition = camera == NULL ? Vec2() : camera->getTransform()->getPosition();

  _selfTransform->setPosition(cameraPosition + _offset);

  for (size_t i = 0; i < _layerSizes.size(); ++i) {
    const auto layerRTransform = _layerTransforms[i * 2];
    const auto layerLTransform = _layerTransforms[i * 2 + 1];
    const auto layerSize = _layerSizes[i];

    _layerMovingOffset[i] += (i + 1) * _coef * ABS(_movingSpeed);
    _layerMovingOffset[i] = std::fmodf(_layerMovingOffset[i], layerSize);

    auto d = cameraPosition.getX() * (i + 1) * _coef;
    if (_movingSpeed > 0) {
      d += _layerMovingOffset[i];
    }
    else if (_movingSpeed < 0) {
      d -= _layerMovingOffset[i];
    }

    while (d < 0) d += layerSize;
    d = std::fmodf(d, layerSize);

    const auto offset = -layerSize + d;
    layerLTransform->setPositionX(offset);
    layerRTransform->setPositionX(offset + layerSize);
  }
}
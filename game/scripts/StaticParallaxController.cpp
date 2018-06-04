#include "StaticParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(StaticParallaxController, ala::GameObjectComponent)

StaticParallaxController::StaticParallaxController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _coef(0.1f), _selfTransform(NULL) {}

void StaticParallaxController::setOffset(const ala::Vec2& offset) {
  _offset = offset;
}

void StaticParallaxController::setCoef(const float speed) {
  _coef = speed;
}

void StaticParallaxController::onInitialize() {
  _selfTransform = getGameObject()->getTransform();

  const auto& transformChildren = _selfTransform->getChildren();
  for (size_t i = 0; i < transformChildren.size() - 1; i += 2) {
    const auto transformChildR = transformChildren[i];
    const auto transformChildL = transformChildren[i + 1];

    _layerTransforms.push_back(transformChildR);
    _layerTransforms.push_back(transformChildL);
    _layerSizes.push_back(transformChildR->getGameObject()->getComponentT<SpriteRenderer>()
      ->getFrameSize().getWidth());
  }
}

void StaticParallaxController::onRender() {
  const auto gameManager = GameManager::get();
  const auto camera = gameManager->getRunningScene()->getMainCamera();
  const auto cameraPosition = camera == NULL ? Vec2() : camera->getTransform()->getPosition();

  _selfTransform->setPosition(cameraPosition + _offset);

  for (size_t i = 0; i < _layerSizes.size(); ++i) {
    const auto layerRTransform = _layerTransforms[i * 2];
    const auto layerLTransform = _layerTransforms[i * 2 + 1];
    const auto layerSize = _layerSizes[i];

    auto d = cameraPosition.getX() * (i + 1) * _coef + 1000;
    d = std::fmodf(d, layerSize);

    const auto offset = -layerSize + d;
    layerLTransform->setPositionX(offset);
    layerRTransform->setPositionX(offset + layerSize);
  }
}
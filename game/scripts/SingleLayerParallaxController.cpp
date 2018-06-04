#include "SingleLayerParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SingleLayerParallaxController, ala::GameObjectComponent)

SingleLayerParallaxController::SingleLayerParallaxController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _offset(0, 0), _coef(1, 1), _selfTransform(NULL) {}

void SingleLayerParallaxController::setOffset(const ala::Vec2& v) {
  _offset = v;
}

void SingleLayerParallaxController::setCoef(const ala::Vec2& v) {
  _coef = v;
}

void SingleLayerParallaxController::onInitialize() {
  _selfTransform = getGameObject()->getTransform();
}

void SingleLayerParallaxController::onRender() {
  const auto gameManager = GameManager::get();
  const auto camera = gameManager->getRunningScene()->getMainCamera();
  const auto cameraPosition = camera == NULL ? Vec2() : camera->getTransform()->getPosition();

  _selfTransform->setPosition(cameraPosition.getX() * _coef.getX() + _offset.getX(),
    cameraPosition.getY() * _coef.getY() + _offset.getY() - 10);
}
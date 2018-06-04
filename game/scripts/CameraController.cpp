#include "CameraController.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CameraController, ala::GameObjectComponent)

CameraController::CameraController(ala::GameObject* gameObject, const std::string& name)
  : GameObjectComponent(gameObject, name), _targetPosition(0, 0), _movingSpeed(7.0f),
  _selfTransform(NULL),
  _aladdinTransform(NULL), _aladdinStateManager(NULL), _aladdinDirection(NULL), _aladdinAnimator(NULL),
  _backgroundLeft(0), _backgroundRight(0),
  _backgroundTop(0), _backgroundBottom(0), _firstSet(false) {}

void CameraController::onInitialize() {
  const auto gameManager = GameManager::get();

  const auto halfVisibleWidth = gameManager->getVisibleWidth() / 2;
  const auto halfVisibleHeight = gameManager->getVisibleHeight() / 2;

  const auto background = gameManager->getObjectByTag(BACKGROUND_TAG);
  if (background != NULL) {
    const auto& backgroundPosition = background->getTransform()->getPosition();
    const auto& backgroundFrameSize = background->getComponentT<SpriteRenderer>()
      ->getFrameSize();

    _backgroundLeft = backgroundPosition.getX() - backgroundFrameSize.getWidth() / 2;
    _backgroundRight = backgroundPosition.getX() + backgroundFrameSize.getWidth() / 2;
    _backgroundTop = backgroundPosition.getY() + backgroundFrameSize.getHeight() / 2;
    _backgroundBottom = backgroundPosition.getY() - backgroundFrameSize.getHeight() / 2;
  }

  _selfTransform = getGameObject()->getTransform();

  const auto aladdin = gameManager->getObjectByTag(ALADDIN_TAG);
  if (aladdin != NULL) {
    _aladdinTransform = aladdin->getTransform();
    _aladdinStateManager = aladdin->getComponentT<StateManager>();
    _aladdinAnimator = aladdin->getComponentT<Animator>();
    _aladdinDirection = aladdin->getComponentT<AladdinController>();

    _selfTransform->setPosition(_aladdinTransform->getPosition());

    // guard camera in background bounding zone
    if (_selfTransform->getPositionX() - _backgroundLeft < halfVisibleWidth) {
      _selfTransform->setPositionX(_backgroundLeft + halfVisibleWidth);
    }
    else if (_backgroundRight - _selfTransform->getPositionX() < halfVisibleWidth) {
      _selfTransform->setPositionX(_backgroundRight - halfVisibleWidth);
    }
    if (_selfTransform->getPositionY() - _backgroundBottom < halfVisibleHeight) {
      _selfTransform->setPositionY(_backgroundBottom + halfVisibleHeight);
    }
    else if (_backgroundTop - _selfTransform->getPositionY() < halfVisibleHeight) {
      _selfTransform->setPositionY(_backgroundTop - halfVisibleHeight);
    }
  }
}

void CameraController::onRender()
{
  if (_aladdinTransform == NULL) return;

  const auto gameManager = GameManager::get();
  const auto input = Input::get();

  const auto halfVisibleWidth = gameManager->getVisibleWidth() / 2;
  const auto halfVisibleHeight = gameManager->getVisibleHeight() / 2;

  const auto& aladdinPosition = _aladdinTransform->getPosition();

  if (!_firstSet) {
    _firstSet = true;
    _selfTransform->setPosition(aladdinPosition);

    // guard camera in background bounding zone
    if (_selfTransform->getPositionX() - _backgroundLeft < halfVisibleWidth) {
      _selfTransform->setPositionX(_backgroundLeft + halfVisibleWidth);
    }
    else if (_backgroundRight - _selfTransform->getPositionX() < halfVisibleWidth) {
      _selfTransform->setPositionX(_backgroundRight - halfVisibleWidth);
    }
    if (_selfTransform->getPositionY() - _backgroundBottom < halfVisibleHeight) {
      _selfTransform->setPositionY(_backgroundBottom + halfVisibleHeight);
    }
    else if (_backgroundTop - _selfTransform->getPositionY() < halfVisibleHeight) {
      _selfTransform->setPositionY(_backgroundTop - halfVisibleHeight);
    }

    return;
  }

  // aladdin horizonta l direction
  if (_aladdinDirection->getHorizontalDirectionScalar() == 1) {
    _targetPosition.setX(aladdinPosition.getX() + halfVisibleWidth * 0.25f);
  }
  else if (_aladdinDirection->getHorizontalDirectionScalar() == -1) {
    _targetPosition.setX(aladdinPosition.getX() - halfVisibleWidth * 0.25f);
  }

  // aladdin vertical direction
  if (_aladdinStateManager != NULL &&
    (_aladdinStateManager->getCurrentStateName() == "look-up" ||
      _aladdinStateManager->getCurrentStateName() == "look-up-attack" ||
      _aladdinStateManager->getCurrentStateName() == "look-up-throw")) {
    _targetPosition.setY(aladdinPosition.getY() + halfVisibleHeight * 0.7f);
  }
  else if (_aladdinStateManager != NULL &&
    (_aladdinStateManager->getCurrentStateName() == "sitdown")) {
    _targetPosition.setY(aladdinPosition.getY() - halfVisibleHeight * 0.7f);
  }
  else {
    _targetPosition.setY(aladdinPosition.getY() - halfVisibleHeight * 0.1f);
  }

  // guard camera in background bounding zone
  if (_targetPosition.getX() - _backgroundLeft < halfVisibleWidth) {
    _targetPosition.setX(_backgroundLeft + halfVisibleWidth);
  }
  else if (_backgroundRight - _targetPosition.getX() < halfVisibleWidth) {
    _targetPosition.setX(_backgroundRight - halfVisibleWidth);
  }
  if (_targetPosition.getY() - _backgroundBottom < halfVisibleHeight) {
    _targetPosition.setY(_backgroundBottom + halfVisibleHeight);
  }
  else if (_backgroundTop - _targetPosition.getY() < halfVisibleHeight) {
    _targetPosition.setY(_backgroundTop - halfVisibleHeight);
  }

  // move camera toward target
  const auto diff = _targetPosition - _selfTransform->getPosition();
  const auto diffLength = diff.getLength();
  if (diffLength <= _movingSpeed) {
    auto curentPos = _selfTransform->getPosition();
    curentPos.smooth(_targetPosition, 0.05, 0.5);
    _selfTransform->setPosition(curentPos);
  }
  else {
    const auto normalizedDiff = diff / diffLength;
    auto curentPos = _selfTransform->getPosition();
    curentPos.smooth(_targetPosition, 0.05, 0.5);
    _selfTransform->setPosition(curentPos);
  }
}

void CameraController::onRelease() {}
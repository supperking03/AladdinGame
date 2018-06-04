#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include <aladdin.h>
#include "AladdinController.h"
#include "AladdinController.h"

ALA_CLASS_HEADER_1(CameraController, ala::GameObjectComponent)
private:
  ala::Vec2 _targetPosition;
  float _movingSpeed;

  ala::Transform* _selfTransform;
  ala::Transform* _aladdinTransform;
  ala::StateManager* _aladdinStateManager;
  AladdinController* _aladdinDirection;
  ala::Animator* _aladdinAnimator;

  float _backgroundLeft;
  float _backgroundRight;
  float _backgroundTop;
  float _backgroundBottom;

  bool _firstSet;

public:
  CameraController(ala::GameObject* gameObject, const std::string& name = "");

protected:
  void onInitialize() override;

  void onRender() override;

  void onRelease() override;
};

#endif // !__CAMERA_CONTROLLER_H__
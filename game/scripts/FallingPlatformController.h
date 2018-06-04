#ifndef __FALLING_PLATFORM_CONTROLLER_H__
#define __FALLING_PLATFORM_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FallingPlatformController, ala::GameObjectComponent)
private:
  bool _collidedWithGround;
  bool _collidedWithAladdin;
  ala::Vec2 _startPosition;
public:
  FallingPlatformController(ala::GameObject* gameObject, const std::string& name = "");

  const ala::Vec2& getStartPosition() const;

  bool isCollidedWithGround() const;

  bool isCollidedWithAladdin() const;

  void onCollisionStay(const ala::CollisionInfo& collision) override;

  void onInitialize() override;

  void onCollisionExit(const ala::CollisionInfo& collision) override;

  void startAladdinCheck();
  void startGroundCheck();
};

#endif// __FALLING_PLATFORM_CONTROLLER_H__
#ifndef __THROWING_APPLE_CONTROLLER_H__
#define __THROWING_APPLE_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(ThrowingAppleController, ala::GameObjectComponent)
private:
  bool _collidedWithGround;
  bool _collidedWithWall;
  bool _collidedWithEnemy;
  bool _collidedWithMapBlocker;
public:
  ThrowingAppleController(ala::GameObject* gameObject, const std::string& name = "");

  bool isCollidedWithGround() const;

  bool isCollidedWithEnemy() const;

  bool isCollidedWithWall() const;

  bool isCollidedWithMapBlocker() const;

  void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif// __THROWING_APPLE_CONTROLLER_H__
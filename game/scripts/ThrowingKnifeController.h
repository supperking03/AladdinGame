#ifndef __THROWING_KNIFE_CONTROLLER_H__
#define __THROWING_KNIFE_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(ThrowingKnifeController, ala::GameObjectComponent)
private:
  bool _collidedWithGround;
  bool _collidedWithWall;
  bool _collidedWithEnemy;
  bool _collidedWithAladdin;
public:
  ThrowingKnifeController(ala::GameObject* gameObject, const std::string& name = "");

  bool isCollidedWithGround() const;

  bool isCollidedWithEnemy() const;

  bool isCollidedWithWall() const;

  bool isCollidedWithAladdin() const;

  void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif// __THROWING_KNIFE_CONTROLLER_H__
#ifndef __POT_CONTROLLER_H__
#define __POT_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PotController, ala::GameObjectComponent)
private:
  bool _collidedWithGround;
  bool _colliedWithAladdin;
  ala::Transform* _transform;
  int _health;
public:
  PotController(ala::GameObject* gameObject, int health, const std::string& name = "");

  bool isCollidedWithGround() const;

  bool isCollidedWithAladdin() const;

  void onInitialize() override;

  void onTriggerEnter(const ala::CollisionInfo& collision) override;

  void onCollisionExit(const ala::CollisionInfo& collision) override;

  int getHealth() const;
  void setHealth(const int health);

  void onOutOfHealth() const;
  void onHit(const int damage);
};

#endif// __POT_CONTROLLER_H__
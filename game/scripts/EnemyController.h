#ifndef __STAFF_GUARD_CONTROLLER_H__
#define __STAFF_GUARD_CONTROLLER_H__

#include <aladdin.h>
#include "EnemyDirectionController.h"
#include "WeaponController.h"


ALA_CLASS_HEADER_1(EnemyController, ala::GameObjectComponent)
protected:
  float _maxYDistance;
  float _startX;
  float _minX;
  float _maxX;

  int _health;

  EnemyDirectionController* _directionController;
  ala::Transform* _aladdinTransform;
  ala::Transform* _transform;
  ala::StateManager* _stateManager;

  float _maxAttackRange;
  float _resetRange;

  bool _collidingCharcoalBurner;

  std::function<int(WeaponController*)> _damageCalculator;
public:
  EnemyController(ala::GameObject* gameObject, int health, const std::function<int(WeaponController*) >& damageCalculator, const std::string& name = "");

  bool isCollidingCharcoalBurner() const;

  bool willReset() const;

  bool canSeeAladdin() const;

  bool canAttackAladdin() const;

  bool canGoLeft() const;

  bool canGoRight() const;

  void clampPosition() const;

  void updateDirection() const;

  float getStartX() const;
  float getMinX() const;
  float getMaxX() const;
  void setStartX(const float startX);
  void setMinX(const float minX);
  void setMaxX(const float maxX);

  float getMaxAttackRange() const;
  void setMaxAttackRange(const float maxAttackRange);

  float getMaxYDistance() const;
  void setMaxYDistance(const float maxYDistance);

  int getHealth() const;
  void setHealth(const int health);

  void onInitialize() override;
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void onTriggerExit(const ala::CollisionInfo& collision) override;
  virtual void onOutOfHealth() const;
  virtual void onHit(WeaponController* weaponController);
};

#endif //!__STAFF_GUARD_CONTROLLER_H__

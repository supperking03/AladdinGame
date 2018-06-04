#ifndef __JAFAR_CONTROLLER_H__
#define __JAFAR_CONTROLLER_H__
#include "core/GameObjectComponent.h"
#include "extra/Timer.h"
#include "core/StateManager.h"
#include "EnemyController.h"

ALA_CLASS_HEADER_1(JafarController, EnemyController)
private:
  int _shoot;

  ala::StateManager* _stateManager;
  ala::StateManager* _aladdinStateManager;
  ala::Transform* _transform;
  ala::Timer* _spawnTimer;
  ala::Timer* _turnTimer;

  int _health;
public:
  JafarController(ala::GameObject* gameObject, const int health, const std::function<int(WeaponController*)> damageCalculator, const std::string& name = "");
  virtual ~JafarController();
  void onInitialize() override;
  void onUpdate(const float delta) override;

void onTriggerEnter(const ala::CollisionInfo& collision) override;

  void onOutOfHealth() const override;
  void onHit(WeaponController* weaponController) override;
};

#endif //!__APPLE_CONTROLLER_H__
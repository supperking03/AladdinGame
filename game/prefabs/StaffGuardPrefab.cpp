#include "StaffGuardPrefab.h"
#include "../Macros.h"
#include "../scripts/EnemyDirectionController.h"
#include "../scripts/EnemyController.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

void StaffGuardPrefab::doInstantiate(ala::GameObject* object) const {

  // components
  new SpriteRenderer(object, "guards.png");

  const auto transform = object->getTransform();

  const auto animator = new Animator(object, "thin_guard_idle", "guards.anm");

  const auto body = new Rigidbody(object, PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 1.0f);

  const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
  collider->setTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_TAG);

  const auto staffCollider = new Collider(object, true, Vec2(50, 5), Size(50, 32), 0, 0, "Sword");
  staffCollider->setTag(ENEMY_WEAPON_TAG);
  staffCollider->ignoreTag(ENEMY_TAG);
  staffCollider->setActive(false);

  const auto stateManager = new StateManager(object, "idle");

  const auto directionController = new EnemyDirectionController(object);

  const auto controller = new EnemyController(object, 2, [](WeaponController* weaponController)
  {
    return weaponController->getDamage();
  });

  // helpers
  const auto attackTimer = new Timer(object);
  const auto staffTimer = new Timer(object);

  // collider renderers
  new ColliderRenderer( collider );
  
  new ColliderRenderer(staffCollider);

  new WeaponController(object, WEAPON_TYPE_ENEMY_STAFF, 1);

  // configurations
  object->setLayer("Character");
  object->setTag(ENEMY_TAG);

  // states
  new State(stateManager, "idle",
    [=] {
    animator->setAction("thin_guard_idle");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    staffCollider->setActive(false);
    attackTimer->start(0.45f);
  }, 
    [=] (float dt){
      if(controller->willReset())
      {
        transform->setPositionX(controller->getStartX());
      }
      if(directionController->getAladdinDirection() < 1)
      {
        directionController->setLeft();
      }
      else
      {
        directionController->setRight();
      }
  }, NULL);

  new State(stateManager, "run",
    [=] {
    animator->setAction("thin_guard_run");
  }, 
    [=](float dt) {
    body->setVelocity(Vec2(100.0f, body->getVelocity().getY()));

    if (directionController->getAladdinDirection() < 1)
    {
      directionController->setLeft();
    }
    else
    {
      directionController->setRight();
    }
  }, NULL);

  new State(stateManager, "attack",
    [=] {
    animator->setAction("thin_guard_attack");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    staffTimer->start(0.15f);
  },
    [=](float dt) {
    if (directionController->getAladdinDirection() < 1)
    {
      directionController->setLeft();
    }
    else
    {
      directionController->setRight();
    }

    if (staffTimer->isDone()) {
      if (!staffCollider->isActive()) {
        staffCollider->setActive(true);
        staffTimer->start(0.2f);
      }
      else {
        staffCollider->setActive(false);
        staffTimer->start(1000);
      }
    }
  },
    [=] {
    staffCollider->setActive(false);
  });

  new State(stateManager, "hit",
    [=] {
    animator->setAction("thin_guard_hit");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
  }, NULL, NULL);

  new StateTransition(stateManager, "idle", "run", [=] {
    return controller->canSeeAladdin() && !controller->canAttackAladdin() &&
      ((directionController->isRight() && controller->canGoRight()) ||
      (directionController->isLeft() && controller->canGoLeft()));
  });

  new StateTransition(stateManager, "run", "idle", [=] {
    return controller->canAttackAladdin() ||
      (directionController->isLeft() && !controller->canGoLeft()) ||
      (directionController->isRight() && !controller->canGoRight());
  });

  new StateTransition(stateManager, "idle", "attack", [=] {
    return controller->canAttackAladdin() && attackTimer->isDone();
  });

  new StateTransition(stateManager, "attack", "idle", [=] {
    return !animator->isPlaying();
  });

  new StateTransition(stateManager, "hit", "idle", [=] {
    return !animator->isPlaying();
  });
}

#include "SwordGuardPrefab.h"
#include "../Macros.h"
#include "../scripts/EnemyDirectionController.h"
#include "../scripts/EnemyController.h"
#include "../scripts/WeaponController.h"

USING_NAMESPACE_ALA;

void SwordGuardPrefab::doInstantiate(ala::GameObject* object) const {
  const auto transform = object->getTransform();

  new SpriteRenderer(object, "guards.png");

  const auto animator = new Animator(object, "fat_guard_idle", "guards.anm");

  const auto body = new Rigidbody(object, PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 1.0f);

  const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
  collider->setTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_TAG);

  const auto swordCollider = new Collider(object, true, Vec2(50, 5), Size(50, 32),0, 0, "Sword");
  swordCollider->setTag(ENEMY_WEAPON_TAG);
  swordCollider->ignoreTag(ENEMY_TAG);
  swordCollider->setActive(false);

  const auto stateManager = new StateManager(object, "idle");

  const auto directionController = new EnemyDirectionController(object);

  const auto controller = new EnemyController(object, 2, [](WeaponController* weaponController){
    return weaponController->getDamage();
  });

  controller->setMaxAttackRange(100);
  const auto swordTimer = new Timer(object);
  const auto attackTimer = new Timer(object);
  new WeaponController(object, WEAPON_TYPE_ENEMY_SWORD, 1);


  // collider renderers
  new ColliderRenderer(collider);

  new ColliderRenderer(swordCollider);

  // configurations
  object->setLayer("Character");
  object->setTag(ENEMY_TAG);

  // states
  new State(stateManager, "provoke",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("GuardBeckon.wav"));
    animator->setAction("fat_guard_provoke");
  }, NULL, NULL);

  new State(stateManager, "idle",
    [=] {
    animator->setAction("fat_guard_idle");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    swordCollider->setActive(false);
    attackTimer->start(0.45f);
  }, [=] (float dt){
    if(controller->willReset())
    {
      transform->setPositionX(controller->getStartX());
    }
    controller->updateDirection();
  }, NULL);

  new State(stateManager, "run",
    [=] {
    animator->setAction("fat_guard_run");
  }, [=](float dt)
  {
    body->setVelocity(Vec2(100.0f, body->getVelocity().getY()));
    controller->updateDirection();
    controller->clampPosition();

  }, NULL);

  new State(stateManager, "burn",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("Aaah.wav"));
    animator->setAction("fat_guard_fire_jump");
    body->setVelocity(Vec2(60, body->getVelocity().getY()));
  }, [=](float dt)
  {
    if(animator->getCurrentFrameIndex() == 8)
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("Aaah.wav"));
    }
    body->setVelocity(Vec2(60, body->getVelocity().getY()));
    controller->updateDirection();
    controller->clampPosition();
  }, NULL);

  new State(stateManager, "attack",
    [=] {
    int random = rand() % 5;
    if (random < 2)
    {
      animator->setAction("fat_guard_attack_1");
      swordCollider->setOffset(Vec2(30, -5));
      swordCollider->setSize(Size(50, 15));
    }
    else
    {
      animator->setAction("fat_guard_attack_2");
      swordCollider->setOffset(Vec2(45, 20));
      swordCollider->setSize(Size(50, 45));
    }
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    swordTimer->start(0.15f);
  },
    [=](float dt) {
    controller->updateDirection();
    if (swordTimer->isDone()) {
      if (!swordCollider->isActive()) {
        swordCollider->setActive(true);
        swordTimer->start(0.2f);
      }
      else {
        swordCollider->setActive(false);
        swordTimer->start(5);
      }
    }
  },
    [=] {
    swordCollider->setActive(false);
  });

  new State(stateManager, "hit",
    [=] {
    animator->setAction("fat_guard_hit");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
  }, NULL, NULL);

  new StateTransition(stateManager, "idle", "provoke", [=] {
    return  (rand() % 5 < 2) && controller->canSeeAladdin() && !controller->canAttackAladdin() &&
      ((directionController->isRight() && controller->canGoRight()) ||
      (directionController->isLeft() && controller->canGoLeft()));
  });

  new StateTransition(stateManager, "idle", "run", [=] {
    return controller->canSeeAladdin() && !controller->canAttackAladdin() &&
      ((directionController->isRight() && controller->canGoRight()) ||
      (directionController->isLeft() && controller->canGoLeft()));
  });


  new StateTransition(stateManager, "provoke", "run", [=] {
    return !animator->isPlaying();
  });

  new StateTransition(stateManager, "run", "idle", [=] {
    return controller->canAttackAladdin() ||
      ((directionController->isRight() && !controller->canGoRight()) ||
      (directionController->isLeft() && !controller->canGoLeft()));
  });

  new StateTransition(stateManager, "run", "burn", [=] {
    return controller->isCollidingCharcoalBurner();
  });

  new StateTransition(stateManager, "burn", "run", [=] {
    return !controller->isCollidingCharcoalBurner();
  });

  new StateTransition(stateManager, "idle", "attack", [=] {
    return controller->canAttackAladdin() && attackTimer->isDone();
  });

  new StateTransition(stateManager, "attack", "idle", [=] {
    return !animator->isPlaying();
  });
  new StateTransition(stateManager, "hit", "burn", [=] {
    return stateManager->getPreviousStateName() == "burn" && !animator->isPlaying();
  });
  new StateTransition(stateManager, "hit", "idle", [=] {
    return !animator->isPlaying();
  });
}

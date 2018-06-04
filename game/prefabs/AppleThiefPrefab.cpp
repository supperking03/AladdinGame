#include "AppleThiefPrefab.h"
#include "../Macros.h"
#include "../scripts/EnemyDirectionController.h"
#include "../scripts/WeaponController.h"
#include "../scripts/EnemyController.h"

USING_NAMESPACE_ALA;

void AppleThiefPrefab::doInstantiate(ala::GameObject* object) const {

  //offset

  // components
  new SpriteRenderer(object, "civilian-enemies.png");

  const auto animator = new Animator(object, "apple_thief_idle", "civilian-enemies.anm");

  const auto body = new Rigidbody(object, PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 1.0f);

  const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
  collider->setTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_TAG);

  const auto handCollider = new Collider(object, true, Vec2(20, 5), Size(40, 20), 0, 0);
  handCollider->setTag(ENEMY_WEAPON_TAG);
  handCollider->ignoreTag(ENEMY_TAG);
  handCollider->setActive(false);

  const auto stateManager = new StateManager(object, "idle");

  const auto transform = object->getTransform();

  const auto directionController = new EnemyDirectionController(object);

  const auto controller = new EnemyController(object, 2, [=](WeaponController* weaponController)
  {
    if(weaponController->getType() != WEAPON_TYPE_ALADDIN_SWORD)
    {
      return 0;
    }
    if(stateManager->getCurrentStateName()== "idle")
    {
      return 0;
    }
    return weaponController->getDamage();
  });
  controller->setMaxAttackRange(60);

  new WeaponController(object, WEAPON_TYPE_ENEMY_STEAL, 3);


  // helpers
  const auto idleTimer = new Timer(object);
  const auto attackTimer = new Timer(object);
  const auto attackDelayTimer = new Timer(object);


  // collider renderers
  new ColliderRenderer(collider);

  new ColliderRenderer(handCollider);

  // configurations
  object->setLayer("Character");
  object->setTag(ENEMY_TAG);


  new State(stateManager, "idle",
    [=] {
    animator->setAction("apple_thief_idle");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    handCollider->setActive(false);
    idleTimer->start((rand() % (2000 - 300) + 300) / 1000.0f);
    attackDelayTimer->start(1.2f);
  }, [=](float dt)
  {
    OutputDebugString("x: ");
    OutputDebugString(std::to_string(transform->getPositionX()).c_str());
    OutputDebugString(" ");
    OutputDebugString("y: ");
    OutputDebugString(std::to_string(transform->getPositionY()).c_str());
    OutputDebugString("\n");
    if (!animator->isPlaying() && idleTimer->isDone()) 
    {
      if (animator->getActionName() == "apple_thief_idle") 
      {
        animator->setAction("apple_thief_look");

      }
      else if (animator->getActionName() == "apple_thief_look") 
      {
        animator->setAction("apple_thief_idle");
        idleTimer->start((rand() % (2000 - 300) + 300) / 1000.0f);
      }
    }
    if(controller->willReset())
    {
      transform->setPositionX(controller->getStartX());
    }

    controller->updateDirection();

  }, NULL);

  new State(stateManager, "run",
    [=] {
    animator->setAction("apple_thief_run");
    body->setVelocity(Vec2(20.0f, body->getVelocity().getY()));
  }, [=](float dt)
  {
    OutputDebugString("x: ");
    OutputDebugString(std::to_string(transform->getPositionX()).c_str());
    OutputDebugString(" ");
    OutputDebugString("y: ");
    OutputDebugString(std::to_string(transform->getPositionY()).c_str());
    OutputDebugString("\n");
    body->setVelocity(Vec2(20.0f, body->getVelocity().getY()));

    controller->updateDirection();

    controller->clampPosition();
  }, NULL);


  new State(stateManager, "attack",
    [=] {
    animator->setAction("apple_thief_steal");   
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    attackTimer->start(0.36f);
  },
    [=](float dt) {
    OutputDebugString("x: ");
    OutputDebugString(std::to_string(transform->getPositionX()).c_str());
    OutputDebugString(" ");
    OutputDebugString("y: ");
    OutputDebugString(std::to_string(transform->getPositionY()).c_str());
    OutputDebugString("\n");
    controller->updateDirection();
    if (attackTimer->isDone()) {
      if (!handCollider->isActive()) {
        handCollider->setActive(true);
        attackTimer->start(0.14f);
      }
      else {
        handCollider->setActive(false);
        attackTimer->start(1000);
      }
    }
  },
    [=] {
    handCollider->setActive(false);
  });


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
    return controller->canAttackAladdin() && attackDelayTimer->isDone();
  });

  new StateTransition(stateManager, "attack", "idle", [=] {
    return !animator->isPlaying();
  });

}

#include "KnifeGuardPrefab.h"
#include "../Macros.h"
#include "core/StateTransition.h"
#include "../scripts/EnemyDirectionController.h"
#include "../scripts/EnemyController.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

void KnifeGuardPrefab::doInstantiate(ala::GameObject* object) const
{
  // components
  const auto spriteRenderer = new SpriteRenderer(object, "guards.png");

  const auto animator = new Animator(object, "adorable_guard_idle", "guards.anm");

  const auto body = new Rigidbody(object, PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 1.0f);

  const auto collider = new Collider(object, false, Vec2(0, 0), Size(40, 50));
  collider->setTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_TAG);

  const auto stateManager = new StateManager(object, "idle");

  const auto direction = new EnemyDirectionController(object);

  const auto controller = new EnemyController(object, 1, [](WeaponController* weaponController)
  {
    return weaponController->getDamage() - (rand() % 2);
  });
  controller->setMaxAttackRange(150);

  // helpers
  const auto timer = new Timer(object);
  const auto attackDelayTimer = new Timer(object);

  const auto transform = object->getTransform();

  new ColliderRenderer( collider );

  object->setLayer("Character");
  object->setTag(ENEMY_TAG);

  // states
  new State(stateManager, "idle",
    [=] {
    animator->setAction("adorable_guard_idle");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
  },
    [=](float dt) {
    if (controller->willReset()) 
    {
      transform->setPositionX(controller->getStartX());
      controller->updateDirection();
    }
  }, NULL);

  new State(stateManager, "idle2",
    [=] {
    animator->setAction("adorable_guard_idle2");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
    attackDelayTimer->start(1.f);
  },
    [=](float dt) {
    if (controller->willReset())
    {
      transform->setPositionX(controller->getStartX());
      controller->updateDirection();
    }
  }, NULL);

  new State(stateManager, "throw",
    [=] {
    animator->setAction("adorable_guard_throw");
    timer->start(0.15f);
  },
    [=](float dt) {
    controller->updateDirection();

    if(timer->isDone())
    {
      GameManager::get()->getPrefab("Throwing Knife")->instantiate(object->getTransform()->getPosition())
      ->getComponentT<Rigidbody>()->setVelocity(Vec2(300 * (direction->isLeft()?-1:1), 150));
      timer->start(5);
    }

  }, NULL);

  new State(stateManager, "run",
    [=] {
    animator->setAction("adorable_guard_run");
  },
    [=](float dt) {
    body->setVelocity(Vec2(100.0f, body->getVelocity().getY()));
    controller->updateDirection();
    controller->clampPosition();
  }, NULL);

  new State(stateManager, "hit",
    [=] {
    animator->setAction("adorable_guard_shame");
    body->setVelocity(Vec2(0, body->getVelocity().getY()));
  }, NULL, NULL);

  new StateTransition(stateManager, "idle", "run", [=] {
    return controller->canSeeAladdin() && !controller->canAttackAladdin() &&
      ((direction->isRight() && controller->canGoRight()) ||
      (direction->isLeft() && controller->canGoLeft()));
  });

  new StateTransition(stateManager, "run", "idle", [=] {
    return controller->canAttackAladdin() ||
      (direction->isLeft() && !controller->canGoLeft()) ||
      (direction->isRight() && !controller->canGoRight());
  });

  new StateTransition(stateManager, "idle", "throw", [=] {
    return controller->canAttackAladdin() && attackDelayTimer->isDone();
  });

  new StateTransition(stateManager, "idle2", "throw", [=] {
    return controller->canAttackAladdin() && attackDelayTimer->isDone();
  });

  new StateTransition(stateManager, "idle2", "idle", [=] {
    return !controller->canAttackAladdin();
  });

  new StateTransition(stateManager, "throw", "idle2", [=] {
    return !animator->isPlaying();
  });

  new StateTransition(stateManager, "hit", "idle", [=] {
    return !animator->isPlaying();
  });
}

#include "ThrowingKnifePrefab.h"
#include "../scripts/ThrowingKnifeController.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

void ThrowingKnifePrefab::doInstantiate(ala::GameObject* object) const {

  // components
  new SpriteRenderer(object, "aladdin.png");
  const auto animator = new Animator(object, "throwable_knife", "guards.anm");

  const auto body = new Rigidbody(object, PhysicsMaterial(3.f, 0.f), ALA_BODY_TYPE_DYNAMIC, 1.0f);
  const auto collider = new Collider(object, true, Vec2(0, 0), Size(4, 5), 1, 0);
  collider->ignoreTag(ENEMY_TAG);
  const auto stateManager = new StateManager(object, "knife_moving");

  const auto controller = new ThrowingKnifeController(object);

  collider->setTag(ENEMY_WEAPON_TAG);

  new WeaponController(object, WEAPON_TYPE_ENEMY_KNIFE, 1);

  // configurations
  object->setLayer("Foreground");

  // states

  new State(stateManager, "knife_destroy", [=] {
    object->release();
  }, NULL, NULL);

  new State(stateManager, "knife_explode",
    [=] {
    animator->setAction("knife_explode");
    body->setVelocity(Vec2(0, 0));
    body->setGravityScale(0);
  }, NULL, NULL);

  new State(stateManager, "knife_moving",
    [=] {
    animator->setAction("throwable_knife");
  }, NULL, NULL);

  new StateTransition(stateManager, "knife_moving", "knife_destroy", [=] {
    return controller->isCollidedWithGround() || controller->isCollidedWithWall() || controller->isCollidedWithAladdin() || controller->isCollidedWithEnemy();
  });

  new StateTransition(stateManager, "knife_moving", "knife_explode", [=] {
    return controller->isCollidedWithGround() || controller->isCollidedWithWall();
  });
  new StateTransition(stateManager, "knife_explode", "knife_destroy", [=] {
    return animator->getActionName() == "apple_explode" && !animator->isPlaying();
  });
}

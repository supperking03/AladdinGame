#include "ThrowingApplePrefab.h"
#include "../scripts/ThrowingAppleController.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

void ThrowingApplePrefab::doInstantiate(ala::GameObject* object) const {

  // components
  new SpriteRenderer(object, "aladdin.png");
  const auto animator = new Animator(object, "apple", "aladdin.anm");

  const auto body = new Rigidbody(object, PhysicsMaterial(3.f, 0.f), ALA_BODY_TYPE_DYNAMIC, 1.0f);
  const auto collider = new Collider(object, true, Vec2(0, 0), Size(8, 10), 1, 0);
  const auto stateManager = new StateManager(object, "apple_moving");

  const auto controller = new ThrowingAppleController(object);

  collider->setTag(ALADDIN_WEAPON_TAG);

  new WeaponController(object, WEAPON_TYPE_ALADDIN_APPLE, 1);

  // configurations
  object->setLayer("Character");

  // states

  new State(stateManager, "apple_destroy", [=] {
    object->release();
  }, NULL, NULL);

  const auto transform = object->getTransform();
  transform->setScale(1.5);

  new State(stateManager, "apple_explode",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("AppleSplat.wav"));
    animator->setAction("apple_explode");
    body->setVelocity(Vec2(0, 0));
    body->setGravityScale(0);
  }, NULL  , NULL);
  new State(stateManager, "apple_half",
    [=] {
    transform->setScale(0.25);
    animator->setAction("half_apple");
    body->setVelocity(Vec2(-body->getVelocity().getX(), body->getVelocity().getY()));
  }, NULL, NULL);

  new State(stateManager, "apple_moving",
    [=] {
    animator->setAction("apple");
  }, NULL, NULL);


  new StateTransition(stateManager, "apple_moving", "apple_explode", [=] {
    return controller->isCollidedWithGround() || controller->isCollidedWithEnemy() || controller->isCollidedWithWall();
  });
  new StateTransition(stateManager, "apple_half", "apple_destroy", [=] {
    return controller->isCollidedWithGround() || controller->isCollidedWithWall();
  });
  new StateTransition(stateManager, "apple_explode", "apple_destroy", [=] {
    return animator->getActionName() == "apple_explode" && !animator->isPlaying();
  });
  new StateTransition(stateManager, "apple_moving", "apple_destroy", [=] {
    return controller->isCollidedWithMapBlocker();
  });
}

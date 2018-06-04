#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "physics/ColliderRenderer.h"
#include "FallingPlatformPrefab.h"
#include "../scripts/PotController.h"
#include "../scripts/FallingPlatformController.h"
#include "../Macros.h"


void FallingPlatformPrefab::doInstantiate(ala::GameObject* object) const
{
  object->setLayer("Character");
  object->setTag(GROUND_TAG);

  ala::Timer* fallTimer = new ala::Timer(object);

  auto spriteRenderer = new ala::SpriteRenderer(object, "fallingplatform.png");
  const auto animator = new ala::Animator(object, "falling-idle", "aladdin.anm");

  new ala::Rigidbody(object, ala::PhysicsMaterial(1, 0), ALA_BODY_TYPE_DYNAMIC, 1, "FallingPlatform");
  const auto collider = new ala::Collider(object, false, ala::Vec2(0, 0), ala::Size(30, 15), 0);
  new ala::ColliderRenderer(collider);
  collider->setTag(GROUND_TAG);
  collider->ignoreTag(ALADDIN_WEAPON_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_WEAPON_TAG);

  const auto controller = new FallingPlatformController(object);


  const auto stateManager = new ala::StateManager(object, "idle");

  //state definitions

  //idle
  new ala::State(stateManager, "idle",
    [=] {
    collider->setTag(GROUND_TAG);
    collider->setActive(true);
    spriteRenderer->setVisible(true);
    animator->setAction("falling-idle");
    controller->startAladdinCheck();
    object->getComponentT<ala::Rigidbody>()->setGravityScale(0);
    object->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(0, 0));
  },NULL, NULL);

  //disappear
  new ala::State(stateManager, "disappear",
    [=] {
    object->getTransform()->setPosition(controller->getStartPosition());
    object->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(0, 0));
    spriteRenderer->setVisible(false);
    collider->setActive(false);
  }, NULL, NULL);
  
  //falling
  new ala::State(stateManager, "falling",
    [=] {
    collider->setTag(ENEMY_TAG);
    animator->setAction("falling-gone");
    fallTimer->start(0.15);
    controller->startGroundCheck();
  }, [=](float dt)
  {
    if(fallTimer->isDone())
    {
      object->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(0, -500));
      fallTimer->start(1000.f);
    }
  }, NULL);

  // state transitions
  new ala::StateTransition(stateManager, "idle", "falling", [=] {
    return controller->isCollidedWithAladdin();
  });

  new ala::StateTransition(stateManager, "falling", "disappear", [=] {
    return controller->isCollidedWithGround();
  });

  new ala::StateTransition(stateManager, "disappear", "idle", [=] {
    return abs(object->getTransform()->getPositionY() - ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getTransform()->getPositionY()) > ala::GameManager::get()->getVisibleHeight() * 0.6f;
  });
}

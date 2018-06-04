#include "ExtraHealthPrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/IntArg.h"
#include "../Macros.h"

void ExtraHealthPrefab::doInstantiate(ala::GameObject* object) const
{
  const auto gameManager = ala::GameManager::get();

  object->setLayer("Items");

  const auto spriteRenderer = new ala::SpriteRenderer(object, "items.png");

  const auto animator = new ala::Animator(object, "extra_health", "items.anm");
  const auto body = new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

  const auto collider = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(10, 10), 1, 0);
  collider->setTag(COLLECTABLE_ITEM_TAG);
  collider->ignoreTag(COLLECTABLE_ITEM_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(GROUND_TAG);
  collider->ignoreTag(ROPE_TAG);
  collider->ignoreTag(WALL_TAG);
  collider->ignoreTag(ROPE_CHECKER_TAG);
  collider->ignoreTag(MAP_BLOCKER_TAG);

  const auto controller = new CollectableItemController(object);

  const auto stateManager = new ala::StateManager(object, "extra_health");


  new ala::State(stateManager, "extra_health", [=] {
    animator->setAction("extra_health");
  }, NULL, NULL);

  new ala::State(stateManager, "collided", [=]
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ExtraHealth.wav"));
    ala::GameManager::get()->getGlobalMessenger()->broadcast(HEALTH_ACQUIRED_MESSAGE, new IntArg(stoi(controller->getValue())));
    gameManager->getPrefab("Twinkle")->instantiate(object->getTransform()->getPosition());
    object->release();
  }, NULL, NULL);

  new ala::StateTransition(stateManager, "extra_health", "collided", [=] {
    return controller->isCollidedWithAladdin();
  });
}

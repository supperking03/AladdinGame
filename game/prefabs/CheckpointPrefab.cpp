#include "CheckpointPrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/Vec2Arg.h"

void CheckpointPrefab::doInstantiate(ala::GameObject* object) const
{
  object->setLayer("Items");

  const auto gameManager = ala::GameManager::get();

  const auto spriteRenderer = new ala::SpriteRenderer(object, "items.png");

  const auto animator = new ala::Animator(object, "checkpoint_off", "items.anm");
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

  //auto controller = new CheckpointController(object);
  const auto controller = new CollectableItemController(object);
  const auto stateManager = new ala::StateManager(object, "checkpoint_off");

  //checkpoint_off
  new ala::State(stateManager, "checkpoint_off",
    [=] {
    animator->setAction("checkpoint_off");
  }, NULL, NULL);

  //checkpoint_on
  new ala::State(stateManager, "checkpoint_on",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("Continue Point.wav"));
    ala::GameManager::get()->getGlobalMessenger()->broadcast(CHECKPOINT_CHECKED_MESSAGE, new Vec2Arg(object->getTransform()->getPosition()));
    animator->setAction("checkpoint_on");
  }, NULL, NULL);

  new ala::StateTransition(stateManager, "checkpoint_off", "checkpoint_on", [=] {
    return controller->isCollidedWithAladdin();
  });
}

#include "CollectableApplePrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/IntArg.h"

void CollectableApplePrefab::doInstantiate(ala::GameObject* object) const
{
  const auto gameManager = ala::GameManager::get();

  object->setLayer("Items");

  new ala::SpriteRenderer(object, "items.png");

  new ala::Animator(object, "apple", "apple.anm");
  new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

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

  const auto stateManager = new ala::StateManager(object, "static");

  new ala::State(stateManager, "static", NULL, NULL, NULL);

  new ala::State(stateManager, "collided", [=]
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(APPLE_ACQUIRED_MESSAGE, new IntArg(stoi(controller->getValue())));
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("AppleCollect.wav"));
    gameManager->getPrefab("Twinkle")->instantiate(object->getTransform()->getPosition());
    object->release();
  }, NULL, NULL);

  new ala::StateTransition(stateManager, "static", "collided", [=]{
    return controller->isCollidedWithAladdin();
  });
}

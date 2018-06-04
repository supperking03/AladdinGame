#include "AbuHeadPrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/IntArg.h"

void AbuHeadPrefab::doInstantiate(ala::GameObject* object) const
{
  object->setLayer("Items");

  const auto gameManager = ala::GameManager::get();

  const auto spriteRenderer = new ala::SpriteRenderer(object, "items.png");

  const auto animator = new ala::Animator(object, "abu_head", "items.anm");
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

  const auto stateManager = new ala::StateManager(object, "abu_head");


  new ala::State(stateManager, "abu_head", [=] {
    animator->setAction("abu_head");
  }, NULL, NULL);

  new ala::State(stateManager, "collided", [=]
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("Wow.wav"));
    gameManager->getPrefab("BigExplosion")->instantiate(object->getTransform()->getPosition());
    object->release();
  }, NULL, NULL);

  new ala::StateTransition(stateManager, "abu_head", "collided", [=] {
    return controller->isCollidedWithAladdin();
  });
}

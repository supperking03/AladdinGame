#include "LampPrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"

void LampPrefab::doInstantiate(ala::GameObject* object) const
{
  object->setLayer("Items");

  const auto gameManager = ala::GameManager::get();

  const auto releaseTimer = new ala::Timer(object);
  const auto spriteRenderer = new ala::SpriteRenderer(object, "items.png");

  const auto animator = new ala::Animator(object, "lamp", "items.anm");
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

  new ala::ColliderRenderer(collider);
  const auto controller = new CollectableItemController(object);

  const auto stateManager = new ala::StateManager(object, "lamp");

  new WeaponController(object, WEAPON_TYPE_ALADDIN_LAMP, std::numeric_limits<int>::max());

  new ala::State(stateManager, "lamp", [=] {
    animator->setAction("lamp");
  }, NULL, NULL);

  new ala::State(stateManager, "collided", [=]
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("GenieFumes.wav"));
    releaseTimer->start(0.5);
    spriteRenderer->setVisible(false);

    auto deleteCollider = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(ala::GameManager::get()->getVisibleWidth() * 2/3, ala::GameManager::get()->getVisibleHeight() * 2/3), 1, 0);
    deleteCollider->setTag(ALADDIN_WEAPON_TAG);
    deleteCollider->ignoreTag(COLLECTABLE_ITEM_TAG);
    deleteCollider->ignoreTag(GROUND_TAG);
    deleteCollider->ignoreTag(ROPE_TAG);
    deleteCollider->ignoreTag(WALL_TAG);
    deleteCollider->ignoreTag(ROPE_CHECKER_TAG);
    deleteCollider->ignoreTag(MAP_BLOCKER_TAG);

    new ala::ColliderRenderer(deleteCollider);

    gameManager->getPrefab("BigTwinkle")->instantiate(object->getTransform()->getPosition() + ala::Vec2(10,40));
  }, [=](float dt)
  {
    if (releaseTimer->isDone())
    {
      object->release();
    }
  }, NULL);

  new ala::StateTransition(stateManager, "lamp", "collided", [=] {
    return controller->isCollidedWithAladdin();
  });
}

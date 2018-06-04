#include "SpringPrefab.h"
#include "../Macros.h"
#include "../scripts/SpringController.h"

void SpringPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "items.png");
  const auto animator = new ala::Animator(object, "spring_0", "items.anm");

  new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

  const auto collider = new ala::Collider(object, true, ala::Vec2(0, -30), ala::Size(38, 10));
  collider->setTag(SPRING_TAG);
  collider->ignoreTag(NPC_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_WEAPON_TAG);
  collider->ignoreTag(GROUND_TAG);
  collider->ignoreTag(ROPE_TAG);
  collider->ignoreTag(ROPE_CHECKER_TAG);
  collider->ignoreTag(HANGER_CHECKER_TAG);
  collider->ignoreTag(HANGER_TAG);
  collider->ignoreTag(ENEMY_WEAPON_TAG);
  collider->ignoreTag(CHARCOAL_BURNER_TAG);
  collider->ignoreTag(COLLECTABLE_ITEM_TAG);
  collider->ignoreTag(SPRING_TAG);
  collider->ignoreTag(MAP_BLOCKER_TAG);

  const auto stateManager = new ala::StateManager(object, "idle");
  new ala::ColliderRenderer(collider);
  object->setTag(SPRING_TAG);
  //object->getTransform()->setScaleX(-1);

  const auto controller = new SpringController(object);

  new ala::State(stateManager, "idle",
    [=] {
    animator->setAction("spring_0");

  }, NULL, NULL);

  new ala::State(stateManager, "jump",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("Flagpole.wav"));
    animator->setAction("spring");
  },NULL, NULL);

  new ala::StateTransition(stateManager, "idle", "jump", [=] {
    return controller->isCollidedWithAladdin();
  });

  new ala::StateTransition(stateManager, "jump", "idle", [=] {
    return !animator->isPlaying();
  });
}

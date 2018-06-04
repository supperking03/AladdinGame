#include "CamelPrefab.h"
#include "../Macros.h"
#include "../scripts/CamelController.h"

void CamelPrefab::doInstantiate(ala::GameObject* object) const
{
  object->setLayer("NPCs");

  new ala::SpriteRenderer(object, "camel.png");
  const auto animator = new ala::Animator(object, "idle", "camel.anm");

  new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

  const auto collider = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(30, 15));
  collider->setTag(NPC_TAG);
  collider->ignoreTag(NPC_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_WEAPON_TAG);
  collider->ignoreTag(GROUND_TAG);
  collider->ignoreTag(ROPE_TAG);
  collider->ignoreTag(MAP_BLOCKER_TAG);
  collider->ignoreTag(ROPE_CHECKER_TAG);
  collider->ignoreTag(HANGER_CHECKER_TAG);
  collider->ignoreTag(HANGER_TAG);
  collider->ignoreTag(ENEMY_WEAPON_TAG);
  collider->ignoreTag(CHARCOAL_BURNER_TAG);
  collider->ignoreTag(COLLECTABLE_ITEM_TAG);

  const auto stateManager = new ala::StateManager(object, "idle");
  new ala::ColliderRenderer(collider);
  object->setTag(NPC_TAG);

  const auto puffTimer = new ala::Timer(object);

  const auto controller = new CamelController(object);

  new ala::State(stateManager, "idle",
    [=] {
    animator->setAction("idle");

  }, NULL, NULL);

  new ala::State(stateManager, "puff",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("CamelSpit.wav"));
    animator->setAction("puff");

    puffTimer->start(0.3f);
  }, [=](float dt) {

    if (puffTimer->isDone()) {
      controller->puffSaliva();
      puffTimer->start(10.f);
    }
  }, NULL);

  new ala::StateTransition(stateManager, "idle", "puff", [=] {
    return controller->isCollidedWithAladdin();
  });

  new ala::StateTransition(stateManager, "puff", "idle", [=] {
    return !animator->isPlaying();
  });
}

#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "physics/ColliderRenderer.h"
#include "PotPrefab.h"
#include "../scripts/PotController.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"


void PotPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "civilian-enemies.png");
  const auto animator = new ala::Animator(object, "pot_falling", "civilian-enemies.anm");
  object->setLayer("Character");

   auto rb = new ala::Rigidbody(object, ala::PhysicsMaterial(1, 0), ALA_BODY_TYPE_DYNAMIC, 1, "Pot");
  const auto collider = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(30, 15), 0);
  new ala::ColliderRenderer(collider);

  collider->setTag(ENEMY_WEAPON_TAG);

  const auto controller = new PotController(object,1);


  const auto stateManager = new ala::StateManager(object, "pot_falling");

  new WeaponController(object, WEAPON_TYPE_ENEMY_POT, 1);

  //state definitions

  //pot_destroyed
  new ala::State(stateManager, "pot_destroyed",
    [=] {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("ClayPot.wav"));
    collider->setActive(false);
    animator->setAction("pot_destroyed");
    rb->setGravityScale(0);
    rb->setVelocity(ala::Vec2(0, 0));
  }, [=](float dt)
  {
    if(!animator->isPlaying())
    {
      object->release();
    }
  }, NULL);

  //pot_falling
  new ala::State(stateManager, "pot_falling",
    [=] {
    rb->setVelocity(ala::Vec2(25, rb->getVelocity().getY()));
    animator->setAction("pot_falling");
  }, NULL, NULL);

  // state transitions
  new ala::StateTransition(stateManager, "pot_falling", "pot_destroyed", [=] {
    return  controller->isCollidedWithGround();
  });

}

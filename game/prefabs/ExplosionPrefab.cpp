#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "physics/ColliderRenderer.h"
#include "PotPrefab.h"
#include "../scripts/PotController.h"
#include "ExplosionPrefab.h"


void ExplosionPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "enemy_explosion.png");
  const auto animator = new ala::Animator(object, "explosion", "guards.anm");
  object->setLayer("Character");
  object->getTransform()->setScale(ala::Vec2(0.5, 0.5));


  const auto stateManager = new ala::StateManager(object, "explosion");

  //state definitions

  //explosion
  new ala::State(stateManager, "explosion",
    [=] {
    animator->setAction("explosion");
  }, [=](float dt)
  {
    if (!animator->isPlaying())
    {
      object->release();
    }
  }, NULL);

}

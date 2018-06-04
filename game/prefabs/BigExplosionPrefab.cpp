#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "physics/ColliderRenderer.h"
#include "PotPrefab.h"
#include "../scripts/PotController.h"
#include "BigExplosionPrefab.h"


void BigExplosionPrefab::doInstantiate(ala::GameObject* object) const
{
  object->setLayer("Effects");
  new ala::SpriteRenderer(object, "enemy_explosions.png");
  const auto animator = new ala::Animator(object, "hit_jafar", "items.anm");


  const auto stateManager = new ala::StateManager(object, "hit_jafar");

  //state definitions

  //explosion
  new ala::State(stateManager, "hit_jafar",
    [=] {
    animator->setAction("hit_jafar");
  }, [=](float dt)
  {
    if (!animator->isPlaying())
    {
      object->release();
    }
  }, NULL);

}

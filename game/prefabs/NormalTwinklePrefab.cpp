#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "../scripts/PotController.h"
#include "ExplosionPrefab.h"
#include "NormalTwinklePrefab.h"


void NormalTwinklePrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "enemy_explosions.png");
  const auto animator = new ala::Animator(object, "twinkle_normal", "items.anm");
  object->setLayer("Character");


  const auto stateManager = new ala::StateManager(object, "twinkle_normal");

  //state definitions

  //twinkle
  new ala::State(stateManager, "twinkle_normal",
    [=] {
    animator->setAction("twinkle_normal");
  }, [=](float dt)
  {
    if (!animator->isPlaying())
    {
      object->release();
    }
  }, NULL);

}

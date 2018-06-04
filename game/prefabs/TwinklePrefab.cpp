#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "../scripts/PotController.h"
#include "ExplosionPrefab.h"
#include "TwinklePrefab.h"


void TwinklePrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "ItemsExplored.png");
  const auto animator = new ala::Animator(object, "twinkle", "aladdin.anm");
  object->setLayer("Character");

  object->getTransform()->setScale(0.5);


  const auto stateManager = new ala::StateManager(object, "twinkle");

  //state definitions

  //twinkle
  new ala::State(stateManager, "twinkle",
    [=] {
    animator->setAction("twinkle");
  }, [=](float dt)
  {
    if (!animator->isPlaying())
    {
      object->release();
    }
  }, NULL);

}

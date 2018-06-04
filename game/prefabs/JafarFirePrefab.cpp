#include "JafarFirePrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "audio/AudioSource.h"
#include "physics/ColliderRenderer.h"
#include "../scripts/PotController.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"


void JafarFirePrefab::doInstantiate(ala::GameObject* object) const
{
  auto sr = new ala::SpriteRenderer(object, "jafar.png");
  auto animator = new ala::Animator(object, "fire-move", "jafar.anm");
  
  auto rb = new ala::Rigidbody(object, ala::PhysicsMaterial(1, 0), ALA_BODY_TYPE_DYNAMIC, 1, "JafarFire");
  auto cl = new ala::Collider(object, true, ala::Vec2(0, -10), ala::Size(25, 10), 0);
  //new ala::ColliderRenderer(cl);

  auto timer = new ala::Timer(object);
  cl->setTag(ENEMY_WEAPON_TAG);

  auto collision = new PotController(object,100);


  const auto stateManager = new ala::StateManager(object, "fire-fall");

  new WeaponController(object, WEAPON_TYPE_ENEMY_FIRE, 1);

   //state definitions

  //fire-move
  new ala::State(stateManager, "fire-move",
    [=] {
    timer->start(5);
    animator->setAction("fire-move");
    object->getComponentT<ala::Rigidbody>()->setGravityScale(0);
    object->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(object->getComponentT<ala::Rigidbody>()->getVelocity().getX(),0));
  }, [=](float dt)
  {
    if (timer->isDone())
    {
      object->release();
    }
  }, NULL);

  //fire-fall
  new ala::State(stateManager, "fire-fall",
    [=] {
    animator->setAction("fire-move");
  }, NULL, NULL);

  // state transitions
  new ala::StateTransition(stateManager, "fire-fall", "fire-move", [=] {
    return  collision->isCollidedWithGround(); 
  });
}

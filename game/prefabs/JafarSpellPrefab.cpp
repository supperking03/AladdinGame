#include "JafarSpellPrefab.h"
#include "../../aladdin/2d/SpriteRenderer.h"
#include "physics/Rigidbody.h"
#include "physics/Collider.h"
#include "2d/Animator.h"
#include "core/StateManager.h"
#include "audio/AudioSource.h"
#include "physics/ColliderRenderer.h"
#include "../scripts/SpellTriggerChecker.h"
#include "extra/Timer.h"
#include "../scripts/SpellController.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"


void JafarSpellPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "jafar.png");
  const auto animator = new ala::Animator(object, "spell", "jafar.anm");
  auto aladdin = ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getTransform();
  auto jafar = ala::GameManager::get()->getObjectByName("Jafar")->getTransform();
  auto jafarSpell = object->getTransform();

  auto timer = new ala::Timer(object);

  auto rb = new ala::Rigidbody(object, ala::PhysicsMaterial(1, 0), ALA_BODY_TYPE_DYNAMIC, 0, "JafarSpell");
  auto collider = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(10, 10), 0, 0 ,"JafarSpell");
  new ala::ColliderRenderer(collider);

  collider->setTag(ENEMY_WEAPON_TAG);
  collider->ignoreTag(ROPE_CHECKER_TAG);
  collider->ignoreTag(HANGER_CHECKER_TAG);
  collider->ignoreTag(STAIR_CHECKER_TAG);
  collider->ignoreTag(COLLECTABLE_ITEM_TAG);
  collider->ignoreTag(GROUND_TAG);

  auto hitChecker = new SpellController(object);

  const auto stateManager = new ala::StateManager(object, "spell");

  new WeaponController(object, WEAPON_TYPE_ENEMY_SPELL, -80);

  //state definitions

  //spell
  new ala::State(stateManager, "spell",
    [=] {
    animator->setAction("spell");
    object->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(500 * (aladdin->getPositionX() - jafar->getPositionX()) / abs(aladdin->getPositionX() - jafar->getPositionX()), 500 * (aladdin->getPositionY() - jafar->getPositionY()) / abs(aladdin->getPositionY() - jafar->getPositionY())));
  }, NULL, NULL);

  //spell-hit
  new ala::State(stateManager, "spell-hit",
    [=] {
    animator->setAction("spell-hit");    
    //aladdin->setPositionX(aladdin->getPositionX() - 10 * (aladdin->getPositionX() - jafar->getPositionX()) / abs(aladdin->getPositionX() - jafar->getPositionX()));
    rb->setVelocity(ala::Vec2(0, 0));
    rb->setGravityScale(0);
  }, [=](float dt)
  {
    if(!animator->isPlaying())
    {
      object->release();
    }
  }, NULL);

  //spell-return
  new ala::State(stateManager, "spell-return",
    [=] {   
    timer->start(5); 
    //Move-to
    auto distance = aladdin->getPosition() - jafarSpell->getPosition();
    distance.normalize();
    rb->setVelocity(distance * 500);
  }, [=](float delta)
  {
    if(abs(aladdin->getPositionX()-jafarSpell->getPositionX()) > 100 || abs(aladdin->getPositionY() - jafarSpell->getPositionY()) > 100)
    {
      //Move-to
      auto distance = aladdin->getPosition() - jafarSpell->getPosition();
      distance.normalize();
      rb->setVelocity(distance * 500);
    }

    if(timer->isDone())
    {
      //object->release();
    }
  }, NULL);


  new ala::StateTransition(stateManager, "spell", "spell-hit", [=] {
    return hitChecker->isCollidedWithAladdin();
  });
  
  new ala::StateTransition(stateManager, "spell", "spell-return", [=] {
    return  abs(aladdin->getPositionY() - object->getTransform()->getPositionY()) > 50;
  });

  new ala::StateTransition(stateManager, "spell-return", "spell-hit", [=] {
    return hitChecker->isCollidedWithAladdin();
  });

}

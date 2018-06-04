#include "JafarPrefab.h"
#include "../scripts/CameraController.h"
#include "../scripts/JafarController.h"
#include "PotDropperPrefab.h"
#include "../Macros.h"
#include "../scripts/EnemyController.h"
#include "../Macros.h"

/*
* Created by kiennm97 on Nov 14th 2017
*/

void PotDropperPrefab::doInstantiate(ala::GameObject * object) const
{
  auto dropTimer = new ala::Timer(object);
  auto hideTimer = new ala::Timer(object);

  const auto body = new ala::Rigidbody(object, ala::PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 0);

  auto spriteRenderer = new ala::SpriteRenderer(object, "civilian-enemies.png");
  spriteRenderer->setVisible(false);

  const auto animator = new ala::Animator(object, "pot_dropper", "civilian-enemies.anm");

  const auto stateManager = new ala::StateManager(object, "idle");

  const auto controller = new EnemyController(object,1, [=](WeaponController* weaponController){
    if(weaponController->getType() == WEAPON_TYPE_ALADDIN_LAMP)
    {
      return weaponController->getDamage();
    }
    if(!hideTimer->isDone())
    {
      return 0;
    }
    return weaponController->getDamage();
  });

  controller->setMaxAttackRange(50);
  controller->setMaxYDistance(1000);

  const auto collider = new ala::Collider(object,true, ala::Vec2(0, 0), ala::Size(16, 26));
  collider->setTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_TAG);

  new ala::ColliderRenderer(collider);
  //state definitions
  new ala::State(stateManager, "drop_pot",
    [=] {
    collider->setActive(true);
    dropTimer->start(0.49);
    object->getComponentT<ala::SpriteRenderer>()->setVisible(true);
    animator->setAction("pot_dropper");
  }, [=](float dt)
  {
    if(dropTimer->isDone())
    {
      hideTimer->start(0.7);
      dropTimer->start(1000);
      auto pot = ala::GameManager::get()->getPrefab("Pot")->instantiate("Pot");
      pot->getTransform()->setPosition(object->getTransform()->getPositionX()+10, object->getTransform()->getPositionY());
    }
    if (!animator->isPlaying())
    {
      collider->setActive(false);
    }
  },NULL);

  new ala::State(stateManager, "idle",
    [=] {
    object->getComponentT<ala::SpriteRenderer>()->setVisible(false);
  }, NULL, NULL);

   //state transitions
  new ala::StateTransition(stateManager, "drop_pot", "idle", [=] {
    return animator->getActionName() == "pot_dropper" && !animator->isPlaying() && !controller->canAttackAladdin();
  });

  new ala::StateTransition(stateManager, "drop_pot", "drop_pot", [=] {
    return animator->getActionName() == "pot_dropper" && !animator->isPlaying() && hideTimer->isDone();
  });

  new ala::StateTransition(stateManager, "idle", "drop_pot", [=] {
    return controller->canAttackAladdin();
  });

}

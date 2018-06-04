#include "KnifeJugglerPrefab.h"
#include "../Macros.h"
#include "../scripts/EnemyDirectionController.h"
#include "../scripts/EnemyController.h"

void KnifeJugglerPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "civilian-enemies.png");

  const auto animator = new ala::Animator(object, "knife_juggler", "civilian-enemies.anm");

  const auto aladdinTransform = ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getTransform();

  const auto body = new ala::Rigidbody(object, ala::PhysicsMaterial(5.0f), ALA_BODY_TYPE_DYNAMIC, 1.0f);

  const auto collider = new ala::Collider(object, false, ala::Vec2(0, 0), ala::Size(40, 50));
  collider->setTag(ENEMY_TAG);
  collider->ignoreTag(ENEMY_TAG);
  collider->ignoreTag(ALADDIN_TAG);
  new ala::ColliderRenderer(collider);

  const auto direction = new EnemyDirectionController(object);
  auto controller = new EnemyController(object, 2, [](WeaponController* weaponController)
  {
    return weaponController->getDamage();
  });
  controller->setMaxAttackRange(230);
  controller->setMaxYDistance(1000);

  const auto stateManager = new ala::StateManager(object, "idle");

  object->setLayer("Character");
  object->setTag(ENEMY_TAG);

  const auto transform = object->getTransform();

  new ala::State(stateManager, "idle",
    [=] {
    animator->pause();
  }, [=](float delta) {
    controller->updateDirection();
  }, NULL);
  new ala::State(stateManager, "throwing",
    [=] {
    animator->playFromStart();
  }, [=] (float dt) {
    if(animator->isPlaying())
    {
      return;
    }
    controller->updateDirection();
    
    auto distanceToAladdin = abs(aladdinTransform->getPositionX() - transform->getPositionX());
    if(distanceToAladdin >= (controller->getMaxAttackRange()/2.f))
    {
      ala::GameManager::get()->getPrefab("Throwing Knife")->instantiate(object->getTransform()->getPosition())
        ->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(150 * (direction->isLeft() ? -1 : 1), 500));
    }
    else
    {
      ala::GameManager::get()->getPrefab("Throwing Knife")->instantiate(object->getTransform()->getPosition())
        ->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(300 * (direction->isLeft() ? -1 : 1), 150));
    }

    animator->playFromStart();
  }, NULL);

  new ala::StateTransition(stateManager, "idle", "throwing", [=] {
    return controller->canAttackAladdin();
  });
  new ala::StateTransition(stateManager, "throwing", "idle", [=] {
    return !controller->canAttackAladdin();
  });
}

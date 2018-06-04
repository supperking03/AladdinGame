#include "JafarPrefab.h"
#include "physics/Rigidbody.h"
#include "../scripts/CameraController.h"
#include "physics/Collider.h"
#include "../scripts/JafarController.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"

/*
* Created by kiennm97 on Nov 14th 2017
*/

void JafarPrefab::doInstantiate(ala::GameObject * object) const
{
  object->setLayer("NPCs");
  const auto gameManager = ala::GameManager::get();

  object->setTag(JAFAR_TAG);

  const auto aladdin = ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getTransform();

  new ala::SpriteRenderer(object, "jafar.png");
  const auto animator = new ala::Animator(object, "jafar_idle", "jafar.anm");

  const auto child = new ala::GameObject(object);
  child->setLayer("NPCs");

  const auto childSpriteRenderer = new ala::SpriteRenderer(child, "jafar.png");
  childSpriteRenderer->setVisible(false);
  childSpriteRenderer->setZOrder(-1);

  const auto childAnimator = new ala::Animator(child, "fire-hell", "jafar.anm");
  const auto childTransform = child->getTransform();
  childTransform->setPosition(20,-10);

  const auto child2 = new ala::GameObject(object);
  child2->setLayer("NPCs");
  const auto childSpriteRenderer2 = new ala::SpriteRenderer(child2, "jafar.png");
  childSpriteRenderer2->setVisible(false);
  childSpriteRenderer2->setZOrder(-1);

  const auto childAnimator2 = new ala::Animator(child2, "fire-hell", "jafar.anm");
  const auto childTransform2 = child2->getTransform();
  childTransform2->setPosition(0,-10);

  const auto child3 = new ala::GameObject(object);
  child3->setLayer("NPCs");
  const auto childSpriteRenderer3 = new ala::SpriteRenderer(child3, "jafar.png");
  childSpriteRenderer3->setVisible(false);
  childSpriteRenderer3->setZOrder(-1);

  const auto childAnimator3 = new ala::Animator(child3, "fire-hell", "jafar.anm");
  const auto childTransform3 = child3->getTransform();
  childTransform3->setPosition(-20, -10);

  ////set Physics
  new ala::Rigidbody(object, ala::PhysicsMaterial(1, 0), ALA_BODY_TYPE_DYNAMIC, 0);
  auto colider = new ala::Collider(object, true, ala::Vec2(0, -10), ala::Size(30, 50), 1, 0, "Jafar");
  new ala::ColliderRenderer(colider);
  auto controller = new JafarController(object,21, [](WeaponController* weaponController){
    if(weaponController->getType() == WEAPON_TYPE_ALADDIN_APPLE)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  });
  colider->setTag(ENEMY_WEAPON_TAG);

  object->getTransform()->setPosition(ala::Vec2(100, 200));

  new WeaponController(object, WEAPON_TYPE_JAFAR, 1);

  const auto stateManager = new ala::StateManager(object, "jafar_idle");

  new ala::State(stateManager, "snake", [=] {
    childSpriteRenderer->setVisible(true);
    childSpriteRenderer2->setVisible(true);
    childSpriteRenderer3->setVisible(true);
    animator->setAction("snake");
    ala::GameManager::get()->getGlobalMessenger()->broadcast(TURN_ON_CHARCOALBURNER_MESSAGE, NULL);
  }, NULL, NULL);

  new ala::State(stateManager, "jafar_idle", [=] {
    animator->setAction("jafar_idle");
  }, NULL, NULL);

  new ala::State(stateManager, "jafar_fire", [=]
  {
    animator->setAction("jafar_fire");
  }, NULL, NULL);

  new ala::StateTransition(stateManager, "jafar_idle", "jafar_fire", [=] {
    return abs(object->getTransform()->getPositionX() - aladdin->getPositionX()) <= 350;
  });

  new ala::StateTransition(stateManager, "jafar_fire", "jafar_idle", [=] {
    return abs(object->getTransform()->getPositionX() - aladdin->getPositionX()) > 350;
  });
}

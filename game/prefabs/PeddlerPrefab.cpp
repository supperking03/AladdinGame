#include "PeddlerPrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/IntArg.h"
#include "../scripts/PeddlerController.h"

void PeddlerPrefab::doInstantiate(ala::GameObject* object) const
{
  const auto gameManager = ala::GameManager::get();

  object->setLayer("NPCs");

  // components
  const auto spriteRenderer = new ala::SpriteRenderer(object, "peddler.png");

  const auto animator = new ala::Animator(object, "idle_1", "peddler.anm");

  const auto body = new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

  const auto collider10 = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(10, 20));
  collider10->setTag(SHOP_10_TAG);

  const auto collider5 = new ala::Collider(object, true, ala::Vec2(-50, 0), ala::Size(10, 20));
  collider5->setTag(SHOP_5_TAG);

  for (int i = 1; i<=20; ++i)
  {
    collider10->ignoreTag(i);
  }

  auto controller = new PeddlerController(object);

  const auto stateManager = new ala::StateManager(object, "static");


  const auto child = new ala::GameObject(object);

  const auto childSpriteRenderer = new ala::SpriteRenderer(child, "peddler.png");
  childSpriteRenderer->setVisible(false);

  const auto childAnimator = new ala::Animator(child, "idle_1", "peddler.anm");

  const auto childTransform = child->getTransform();
  childTransform->setPositionX(50);

  // helpers
  const auto transform = object->getTransform();

  // collider renderers
  new ala::ColliderRenderer(collider5);
  new ala::ColliderRenderer(collider10);

  // states
  new ala::State(stateManager, "static",
    NULL,
    [=](float dt) {
    if (abs(object->getTransform()->getPositionX() - gameManager->getObjectByTag(ALADDIN_TAG)->getTransform()->getPositionX()) > 200 && animator->getActionName() == "pavilion_2")
    {
      animator->setAction("idle_1");
      childSpriteRenderer->setVisible(false);
    }
    if (abs(object->getTransform()->getPositionX() - gameManager->getObjectByTag(ALADDIN_TAG)->getTransform()->getPositionX()) <= 200 && animator->getActionName() == "idle_1") 
    {
      animator->setAction("pavilion_1");
    }
    else if (animator->getActionName() == "pavilion_1") 
    {
      if (animator->getCurrentFrameIndex() == 24) 
      {
        childSpriteRenderer->setVisible(true);
        childAnimator->setAction("idle_2");
      }

      if (!animator->isPlaying()) 
      {
        animator->setAction("pavilion_2");
      }
    }
  }, NULL);
}

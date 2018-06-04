#include "LevelCompletePrefab.h"
#include "../Macros.h"
#include "../scripts/CollectableItemController.h"
#include "../arguments/IntArg.h"
#include <debugapi.h>
#include "../scenes/CompleteScene.h"

void LevelCompletePrefab::doInstantiate(ala::GameObject* object) const
{
  const auto gameManager = ala::GameManager::get();

  object->setLayer("Items");
  new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_STATIC);

  const auto controller = new CollectableItemController(object);

  const auto stateManager = new ala::StateManager(object, "static");

  new ala::State(stateManager, "static", NULL, NULL, NULL);

  new ala::State(stateManager, "collided", [=]
  {
    ala::GameManager::get()->replaceScene(new CompleteScene());
  }, NULL, NULL);

  new ala::StateTransition(stateManager, "static", "collided", [=] {
    return controller->isCollidedWithAladdin();
  });
}
 
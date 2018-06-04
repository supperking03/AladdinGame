#include "AladdinSceneFadeOutTransitionPrefab.h"
#include "../scripts/FadeInEffect.h"
#include "../scripts/CameraController.h"
#include "../scenes/AladdinScene.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AladdinSceneFadeOutTransitionPrefab, ala::PrefabV2)

void AladdinSceneFadeOutTransitionPrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const {
  // args
  const auto mapResource = nextLine(argsStream);
  // constants
  const auto gameManager = GameManager::get();

  const auto physicsManager = PhysicsManager::get();

  const auto camera = gameManager->getRunningScene()->getMainCamera();

  const auto visibleSize = Size(gameManager->getVisibleWidth(), gameManager->getVisibleHeight());

  // components
  const auto rectRenderer = new RectRenderer(object, Vec2(0, 0), visibleSize, Color(0, 0, 0));
  rectRenderer->setOpacity(0);

  const auto cameraFollower = new CameraController(object);

  const auto fadeIn = new FadeInEffect(object);

  const auto stateManager = new StateManager(object, "default");


  // states
  new State(stateManager, "default",
    [=] {
    // deactive objects in scene
    for (const auto o : gameManager->getAllObjects()) {
      if (o != camera && o != object) {
        o->setActive(false);
      }
    }

    rectRenderer->setOpacity(0);
    fadeIn->start(0.5f);
  },
    [=](float dt) {
    if (!fadeIn->isRunning()) {
      //chuyen scene
      gameManager->replaceScene(new AladdinScene(mapResource));
    }
  },
    NULL);

  // configurations
  object->setLayer("Overlay");
  rectRenderer->setZOrder(90);
}
#include "SandPrefab.h"
#include "../scripts/StaticParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SandPrefab, ala::PrefabV2)

void SandPrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const {
  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer(object, "agrabah_market_parallax.png");

  const auto animator = new Animator(object, "1", "agrabah_market_parallax.anm");

  const auto parallax = new StaticParallaxController(object);
  parallax->setOffset(Vec2(0, -80));
  parallax->setCoef(0.07f);

  //  float layerOffsets[] = { 46.5f, 67.5f, 80.0f, 92.0f, 112.5f, 142.0f, 171.0f, 191.0f };
  float layerOffsets[] = { 46.5f, 67.5f, 80.0f, 92.0f };
  const int numberOfLayers = sizeof(layerOffsets) / sizeof(float);

  for (auto i = 0; i < numberOfLayers; ++i) {
    std::stringstream stringBuilder;
    stringBuilder << i + 2;

    for (auto k = 0; k < 2; ++k) {
      const auto layer = new GameObject(object);
      const auto layerSpriteRenderer = new SpriteRenderer(layer, "agrabah_market_parallax.png");
      const auto layerAnimator = new Animator(layer, stringBuilder.str(), "agrabah_market_parallax.anm");
      layer->getTransform()
        ->setPosition(Vec2(-k * layerSpriteRenderer->getFrameSize().getWidth(), layerOffsets[i]));
      layer->setLayer("Parallax");
    }
  }

  object->setLayer("Parallax");
}
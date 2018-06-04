#include "SkyPrefab.h"
#include "../scripts/DynamicParallaxController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SkyPrefab, ala::PrefabV2)

void SkyPrefab::doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const {
  // constants
  const auto gameManager = GameManager::get();

  // components
  const auto spriteRenderer = new SpriteRenderer(object, "agrabah_market_parallax.png");

  const auto animator = new Animator(object, "6", "agrabah_market_parallax.anm");

  const auto parallax = new DynamicParallaxController(object);
  parallax->setOffset(Vec2(0, 32.5f));
  parallax->setCoef(0.07f);
  parallax->setMovingSpeed(-7.0f);

  float layerOffsets[] = { 29.6f, 58.5f, 78.5f };
  const int numberOfLayers = sizeof(layerOffsets) / sizeof(float);

  for (auto i = 0; i < numberOfLayers; ++i) {
    std::stringstream stringBuilder;
    stringBuilder << i + 7;

    for (auto k = 0; k < 2; ++k) {
      const auto layer = new GameObject(object);
      const auto layerSpriteRenderer = new SpriteRenderer(layer, "agrabah_market_parallax.png");
      const auto layerAnimator = new Animator(layer, stringBuilder.str(), "agrabah_market_parallax.anm");
      layer->getTransform()
        ->setPosition(Vec2(-k * layerSpriteRenderer->getFrameSize().getWidth(), layerOffsets[i] - 1));
      layer->setLayer("Parallax");
    }
  }

  object->setLayer("Parallax");
}

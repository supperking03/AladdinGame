#include "TextPrefab.h"

USING_NAMESPACE_ALA;

void TextPrefab::doInstantiate(ala::GameObject* object) const {
  new RectTransform(object, Rect(Vec2(0, 0),
    GameManager::get()->getVisibleWidth()/2,
    GameManager::get()->getVisibleHeight()/2));
  new Text(object, FontInfo(ALA_FONT_WEIGHT_BOLD, 100), "arcade.ttf", Color(255, 255, 255));
}

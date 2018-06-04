#include "RectRenderer.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_1(ala::RectRenderer, ala::GameObjectComponent)

  RectRenderer::RectRenderer(ala::GameObject* gameObject,
    const ala::Vec2& offset, const ala::Size& size, const Color& color,
    const std::string& name)
  : GameObjectComponent(gameObject, name), _sprite(NULL),
  _offset(offset), _size(size), _alpha(255),
  _zOrder(0) {
  _sprite = GameManager::get()->getEmptySprite(color);
}

int RectRenderer::getZOrder() const { return _zOrder; }

void RectRenderer::setZOrder(const int order) { _zOrder = order; }

const ala::Vec2& RectRenderer::getOffset() const { return _offset; }

void RectRenderer::setOffset(const ala::Vec2& offset) { _offset = offset; }

const ala::Size& RectRenderer::getSize() const { return _size; }

void RectRenderer::setSize(const ala::Size& size) { _size = size; }

float RectRenderer::getOpacity() const {
  return _alpha / 255.0f;
}

void RectRenderer::setOpacity(float opacity) {
  _alpha = MIN(255, MAX(0, (int)(opacity * 255)));
}

void RectRenderer::onRender() {
  const auto transform = getGameObject()->getTransform();
  const auto worldZOrder = calculateWorldZOrder();

  const auto oldPosition = transform->getPosition();
  const auto oldScale = transform->getScale();
  transform->setPositionX(transform->getPositionX() + _offset.getX() * transform->getScale().getX());
  transform->setPositionY(transform->getPositionY() + _offset.getY() * transform->getScale().getY());
  transform->setScale(Vec2(_size.getWidth() * transform->getScale().getX(),
    _size.getHeight() * transform->getScale().getY()));
  Graphics::get()->drawSprite(_sprite,
    Vec2(0.5f, 0.5f), transform->getLocalToWorldMatrix(), Color(255, 255, 255, _alpha),
    Rect(Vec2(0, 0), _sprite->getContentSize()), worldZOrder);
  transform->setPosition(oldPosition);
  transform->setScale(oldScale);
}

int RectRenderer::calculateWorldZOrder() const {
  const auto layerIndex = GameManager::get()->getLayerIndex(getGameObject()->getLayer());
  const auto worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
}

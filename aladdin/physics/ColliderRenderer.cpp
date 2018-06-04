#include "ColliderRenderer.h"
#include "CollisionInfo.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::ColliderRenderer, ala::GameObjectComponent)

ColliderRenderer::ColliderRenderer( ala::Collider* collider,
                                    const float opacity,
                                    const std::string& name )
  : GameObjectComponent( collider->getGameObject(), name ),
    _collider( collider ),
    _backColor( 255, 255, 255, (static_cast<unsigned char>(opacity * 255)) ),
    _zOrder( 0 ) {
  _redSprite = GameManager::get()->getEmptySprite( Color( 255, 0, 0 ) );
  _greenSprite = GameManager::get()->getEmptySprite( Color( 0, 255, 0 ) );
  _blueSprite = GameManager::get()->getEmptySprite( Color( 0, 0, 255 ) );
  _sprite = _redSprite;
}

int ColliderRenderer::getZOrder() const { return _zOrder; }

void ColliderRenderer::setZOrder( const int order ) { _zOrder = order; }

void ColliderRenderer::setOpacity( const float opacity ) {
  _backColor.setA( static_cast<unsigned char>(opacity * 255) );
}

float ColliderRenderer::getOpacity() const {
  return _backColor.getA() / 255.0f;
}

void ColliderRenderer::onRender() {
  if ( _collider == NULL ) return;
  if ( !_collider->isActive() ) return;

  const auto transform = getGameObject()->getTransform();
  const auto worldZOrder = calculateWorldZOrder();

  const auto offset = _collider->getOffset();
  const auto oldPosition = transform->getPosition();
  const auto oldScale = transform->getScale();
  transform->setPositionX( transform->getPositionX() + offset.getX() * transform->getScale().getX() );
  transform->setPositionY( transform->getPositionY() + offset.getY() * transform->getScale().getY() );
  transform->setScale( Vec2( _collider->getSize().getWidth() * transform->getScale().getX(),
                             _collider->getSize().getHeight() * transform->getScale().getY() ) );
 /* Graphics::get()->drawSprite( _sprite,
                               Vec2( 0.5f, 0.5f ), transform->getLocalToWorldMatrix(), _backColor,
                               Rect( Vec2( 0, 0 ), _sprite->getContentSize() ), worldZOrder );*/
  transform->setPosition( oldPosition );
  transform->setScale( oldScale );
}

void ColliderRenderer::onCollisionEnter( const CollisionInfo& collision ) {
  if ( collision.getColliderA() != _collider && collision.getColliderB() != _collider ) return;
  if ( _collider->isTrigger() ) return;
  _sprite = _greenSprite;
}

void ColliderRenderer::onCollisionExit( const CollisionInfo& collision ) {
  if ( collision.getColliderA() != _collider && collision.getColliderB() != _collider ) return;
  if ( _collider->isTrigger() ) return;
  _sprite = _redSprite;
}

void ColliderRenderer::onTriggerEnter( const CollisionInfo& collision ) {
  if ( collision.getColliderA() != _collider && collision.getColliderB() != _collider ) return;
  if ( !_collider->isTrigger() ) return;
  _sprite = _blueSprite;
}

void ColliderRenderer::onTriggerExit( const CollisionInfo& collision ) {
  if ( collision.getColliderA() != _collider && collision.getColliderB() != _collider ) return;
  if ( !_collider->isTrigger() ) return;
  _sprite = _redSprite;
}

int ColliderRenderer::calculateWorldZOrder() const {
  const auto layerIndex = GameManager::get()->getLayerIndex( getGameObject()->getLayer() );
  const auto worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
}

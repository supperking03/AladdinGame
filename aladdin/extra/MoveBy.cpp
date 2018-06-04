#include "MoveBy.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::MoveBy, ala::Action)

MoveBy::MoveBy( const Vec2& distance, const float duration ) : _eslapsedTime( 0 ), _duration( duration ) {
  _velocity = distance / duration;

}

void MoveBy::onStart() {
  _eslapsedTime = 0;
}

void MoveBy::onUpdate( const float delta ) {
  const auto transform = getActionManager()->getGameObject()->getTransform();

  const auto actualDelta = MIN(delta, _duration - _eslapsedTime);

  if ( actualDelta > 0 ) {
    transform->setPosition( transform->getPosition() + _velocity * actualDelta );
    _eslapsedTime += actualDelta;
  }

  if ( _eslapsedTime >= _duration ) done();
}
}

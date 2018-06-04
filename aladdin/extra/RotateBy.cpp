#include "RotateBy.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::RotateBy, ala::Action)

RotateBy::RotateBy( const float angle, const float duration ) : _eslapsedTime( 0 ), _duration( duration ) {
  _velocity = angle / duration;
}

void RotateBy::onStart() {
  _eslapsedTime = 0;
}

void RotateBy::onUpdate( const float delta ) {
  const auto transform = getActionManager()->getGameObject()->getTransform();

  const auto actualDelta = MIN(delta, _duration - _eslapsedTime);

  if ( actualDelta > 0 ) {
    transform->setRotation( transform->getRotation() + _velocity * actualDelta );
    _eslapsedTime += actualDelta;
  }

  if ( _eslapsedTime >= _duration ) done();
}
}

#include "Timer.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Timer, ala::GameObjectComponent )

Timer::Timer( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _timer( 0 ) {}

void Timer::start( const float time ) {
  _timer = time;
}

bool Timer::isDone() const {
  return _timer <= 0;
}

void Timer::onUpdate( const float delta ) {
  if ( _timer > 0 ) _timer -= delta;
}
}

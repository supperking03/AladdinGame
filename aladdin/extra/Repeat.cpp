#include "Repeat.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Repeat, ala::Action)

Repeat::Repeat( Action* action, const int count ): _action( action ),
                                                   _count( count ), _eslapsedCount( 0 ) {}

void Repeat::onStart() {
  _eslapsedCount = 0;
  _action->start( getActionManager() );
}

void Repeat::onUpdate( const float delta ) {
  if ( _action->isDone() ) {
    if ( ++_eslapsedCount == _count ) {
      done();
    }
    else {
      _action->start( getActionManager() );
    }
  }
  else {
    _action->update( delta );
  }
}

void Repeat::onRelease() {
  _action->release();
}
}

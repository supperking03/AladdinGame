#include "Sequence.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Sequence, ala::Action )

Sequence::Sequence( const std::vector<Action*>& actions ) : _actions( actions ) {}

void Sequence::onStart() {
  _currentActionIterator = _actions.cbegin();
  if ( _currentActionIterator == _actions.cend() )
    done();
  else {
    (*_currentActionIterator)->start( getActionManager() );
  }
}

void Sequence::onUpdate( const float delta ) {
  const auto currentAction = *_currentActionIterator;

  if ( currentAction->isDone() ) {
    ++_currentActionIterator;
    if ( _currentActionIterator == _actions.cend() )
      done();
    else {
      (*_currentActionIterator)->start( getActionManager() );
    }
  }
  else {
    currentAction->update( delta );
  }
}

void Sequence::onRelease() {
  for ( const auto action : _actions ) {
    action->release();
  }
}
}

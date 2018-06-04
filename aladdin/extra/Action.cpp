#include "Action.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Action, ala::Releasable )

Action::Action() : _state( 0 ), _actionManager( NULL ) {}

Action::~Action() {}

bool Action::isStarted() const {
  return _state > 0;
}

bool Action::isDone() const {
  return _state > 1;
}

void Action::start( ActionManager* actionManager ) {
  _state = 1;
  _actionManager = actionManager;

  onStart();
}

void Action::update( const float delta ) {
  if ( isStarted() && !isDone() ) {
    onUpdate( delta );
  }
}

void Action::release() {
  onRelease();

  if ( _actionManager != NULL ) {
    _actionManager->removeAction( this );
  }

  delete this;
}

ActionManager* Action::getActionManager() const {
  return _actionManager;
}

void Action::done() {
  _state = 2;
}

void Action::onStart() {}

void Action::onUpdate( float delta ) {}

void Action::onRelease() {}
}

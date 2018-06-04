#include "AnimationAndStateExamplePrefab.h"

USING_NAMESPACE_ALA;

void AnimationAndStateExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  // layer
  object->setLayer( "Character" );

  // sprite renderer
  const auto spriteRenderer = new SpriteRenderer( object, "aladdin.png" );

  // line renderer
  const auto lineRenderer = new LineRenderer( object,
                                              {
                                                ala::Vec2( 50 / 3, 50 / 3 ),
                                                ala::Vec2( 400 / 3, 400 / 3 ),
                                                ala::Vec2( 500 / 3, 200 / 3 ),
                                                ala::Vec2( 600 / 3, 300 / 3 )
                                              },
                                              ala::Color( 255, 255, 0 ) );

  // animator component for animation
  const auto animator = new Animator( object, "stand", "aladdin.animation" );

  // state manager to control object state
  const auto stateManager = new StateManager( object, "stand-right" );

  const auto transform = object->getTransform();
  transform->setScale( 3 );

  // state definitions
  new State( stateManager, "stand-right",
             [=] {
               animator->setAction( "stand" );
             }, NULL, NULL );
  new State( stateManager, "stand-left",
             [=] {
               animator->setAction( "stand" );
             }, NULL, NULL );
  new State( stateManager, "go-right",
             [=] {
               animator->setAction( "run" );
               transform->setScaleX( ABS(transform->getScale().getX()) );
             },
             [=]( float dt ) {
               auto position = transform->getPosition();
               position.setX( position.getX() + 200 * dt );
               transform->setPosition( position );
             },
             NULL );
  new State( stateManager, "go-left",
             [=] {
               animator->setAction( "run" );
               transform->setScaleX( -ABS(transform->getScale().getX()) );
             },
             [=]( float dt ) {
               auto position = transform->getPosition();
               position.setX( position.getX() - 200 * dt );
               transform->setPosition( position );
             },
             NULL );

  // state transitions
  new StateTransition( stateManager, "go-left", "go-right", [] {
    return Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );
  new StateTransition( stateManager, "go-left", "stand-left", [] {
    return Input::get()->getKeyUp( ALA_KEY_LEFT_ARROW );
  } );
  new StateTransition( stateManager, "go-right", "go-left", [] {
    return Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );
  new StateTransition( stateManager, "go-right", "stand-right", [] {
    return Input::get()->getKeyUp( ALA_KEY_RIGHT_ARROW );
  } );
  new StateTransition( stateManager, "stand-left", "go-left", [] {
    return Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );
  new StateTransition( stateManager, "stand-left", "go-right", [] {
    return Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );
  new StateTransition( stateManager, "stand-right", "go-left", [] {
    return Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
  } );
  new StateTransition( stateManager, "stand-right", "go-right", [] {
    return Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
  } );
}

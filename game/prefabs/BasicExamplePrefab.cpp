/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BasicExamplePrefab.h"

USING_NAMESPACE_ALA;

void BasicExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  // layers
  object->setLayer( "Background" );

  new SpriteRenderer( object, "ball.png" );
  new RectRenderer( object, Vec2( 0, 0 ), Size( 30, 30 ), Color( 255, 0, 0 ) );
  new AudioSource( object, "wow.wav" );
}

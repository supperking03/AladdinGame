#include "TextExamplePrefab.h"

USING_NAMESPACE_ALA;

void TextExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  const auto gameManager = GameManager::get();
  const auto visibleWidth = gameManager->getVisibleWidth();
  const auto visibleHeight = gameManager->getVisibleHeight();

  // layer
  object->setLayer( "UI" );

  // create rect transform for ui element rendering
  auto transform = new RectTransform( object, Rect( Vec2( -visibleWidth / 2, visibleHeight / 2 ),
                                                    Size( visibleWidth, visibleHeight ) ) );

  // text component
  auto text = new Text( object, FontInfo( ALA_FONT_WEIGHT_BOLD, 80, false ), "crackman.ttf" );

  text->setText( "Aladdin" );
  text->setTextColor( Color( 255, 255, 255 ) );

  transform->setPosition( 0, 50 );
}

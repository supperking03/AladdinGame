#include "BitmapText.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(BitmapText, ala::GameObjectComponent)

BitmapText::BitmapText( GameObject* gameObject, Sprite* bitmap, BitmapFont* font, const std::string& name )
  : GameObjectComponent( gameObject, name ), _bitmap( bitmap ), _font( font ), _characterSpacing( 0 ),
    _characterAlignment( CENTER ), _textAlignment( CENTER ),
    _visible( true ),
    _zOrder( 0 ) {}

BitmapText::BitmapText( GameObject* gameObject, const std::string& bitmapName, const std::string& fontName,
                        const std::string& name )
  : GameObjectComponent( gameObject, name ), _bitmap( NULL ), _font( NULL ), _characterSpacing( 0 ),
    _characterAlignment( CENTER ), _textAlignment( CENTER ),
    _visible( true ),
    _zOrder( 0 ) {
  _bitmap = static_cast<Sprite*>(GameManager::get()->getResource( bitmapName ));
  _font = static_cast<BitmapFont*>(GameManager::get()->getResource( fontName ));
}

bool BitmapText::isVisible() const {
  return _visible;
}

void BitmapText::setVisible( const bool val ) {
  _visible = val;
}

const std::string& BitmapText::getText() const {
  return _text;
}

void BitmapText::setText( const std::string& text ) {
  _text = text;
}

int BitmapText::getZOrder() const {
  return _zOrder;
}

void BitmapText::setZOrder( const int zOrder ) {
  if ( zOrder < 0 ) _zOrder = 0;
  else if ( zOrder > ALA_MAX_Z_ORDER ) _zOrder = ALA_MAX_Z_ORDER;
  else _zOrder = zOrder;
}

float BitmapText::getCharacterSpacing() const { return _characterSpacing; }

void BitmapText::setCharacterSpacing( const float characterSpacing ) { _characterSpacing = characterSpacing; }

int BitmapText::getCharacterAlignment() const { return _characterAlignment; }

void BitmapText::setCharacterAlignment( const int characterAlignment ) { _characterAlignment = characterAlignment; }

int BitmapText::getTextAlignment() const { return _textAlignment; }

void BitmapText::setTextAlignment( const int textAlignment ) { _textAlignment = textAlignment; }

void BitmapText::onRender() {
  if ( !_visible ) return;

  const auto transform = getGameObject()->getTransform();
  const auto worldZOrder = calculateWorldZOrder();

  std::vector<Rect> charRects;
  float totalWidth = 0;

  for ( const auto c : _text ) {
    if ( c == ' ' ) {
      totalWidth += _font->getCharSpaceWidth() + _characterSpacing;
      charRects.push_back( Rect() );
    }
    else {
      const auto& rect = _font->getCharRect( c );
      totalWidth += rect.getSize().getWidth() + _characterSpacing;
      charRects.push_back( rect );
    }
  }

  if ( charRects.empty() ) return;

  totalWidth -= _characterSpacing;

  const auto oldTransformPosition = transform->getPosition();

  Vec2 charPos;
  switch ( _textAlignment ) {
  case BitmapText::LEFT: charPos.setX( oldTransformPosition.getX() );
    break;
  case BitmapText::RIGHT: charPos.setX( oldTransformPosition.getX() - totalWidth );
    break;
  default: charPos.setX( oldTransformPosition.getX() - totalWidth / 2 );
    break;
  }

  for ( size_t i = 0; i < charRects.size(); ++i ) {
    const auto c = _text[i];
    const auto charRect = charRects[i];

    if ( c == ' ' ) {
      charPos.setX( charPos.getX() + _font->getCharSpaceWidth() + _characterSpacing * 2 );
    }
    else {
      const auto charHalfWidth = charRect.getSize().getWidth() / 2;
      const auto charHalfHeight = charRect.getSize().getHeight() / 2;

      charPos.setX( charPos.getX() + charHalfWidth );
      switch ( _characterAlignment ) {
      case BitmapText::TOP: charPos.setY( oldTransformPosition.getY() - charHalfHeight );
        break;
      case BitmapText::BOTTOM: charPos.setY( oldTransformPosition.getY() + charHalfHeight );
        break;
      default: charPos.setY( oldTransformPosition.getY() );
        break;
      }

      transform->setPosition( charPos );
      Graphics::get()->drawSprite( _bitmap, Vec2( 0.5f, 0.5f ),
                                   transform->getLocalToWorldMatrix(),
                                   Color( 255, 255, 255 ), charRect, worldZOrder );

      charPos.setX( charPos.getX() + charHalfWidth + _characterSpacing );
    }
  }


  transform->setPosition( oldTransformPosition );
}

int BitmapText::calculateWorldZOrder() const {
  const auto layerIndex = GameManager::get()->getLayerIndex( getGameObject()->getLayer() );
  const auto worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
}

#include "BitmapFont.h"
#include "../pugixml/pugixml.hpp"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(BitmapFont, ala::GameResource)

BitmapFont::BitmapFont( const std::string& name, const std::string& sourceFile, Scene* sceneScope )
  : GameResource( name, sceneScope ), _sourceFile( sourceFile ), _charSpaceWidth( 0 ) {}

const ala::Rect& BitmapFont::getCharRect( const char c ) const {
  const auto it = _charRects.find( c );
  if ( it == _charRects.end() ) return _charRects.at( 0 );
  return it->second;
}

float BitmapFont::getCharSpaceWidth() const {
  return _charSpaceWidth;
}

void BitmapFont::onLoad() {
  pugi::xml_document document;
  pugi::xml_parse_result result = document.load_file( _sourceFile.c_str() );

  ALA_ASSERT(result);

  auto charactersNode = document.child( "Characters" );

  Rect rect;

  _charRects.clear();

  auto defaultNode = charactersNode.child( "default" );
  rect.setTopLeft( Vec2( static_cast<float>(defaultNode.attribute( "x" ).as_int()),
                         static_cast<float>(defaultNode.attribute( "y" ).as_int()) ) );
  rect.setSize( Size( static_cast<float>(defaultNode.attribute( "w" ).as_int()),
                      static_cast<float>(defaultNode.attribute( "h" ).as_int()) ) );
  _charRects.emplace( 0, rect );

  auto spaceNode = charactersNode.child( "space" );
  _charSpaceWidth = static_cast<float>(spaceNode.attribute( "w" ).as_int( 0 ));

  auto charNodes = charactersNode.children( "char" );

  for ( auto charNode : charNodes ) {
    const auto c = charNode.attribute( "c" ).as_string( "\0" )[0];
    if ( c == 0 ) continue;

    rect.setTopLeft( Vec2( static_cast<float>(charNode.attribute( "x" ).as_int()),
                           static_cast<float>(charNode.attribute( "y" ).as_int()) ) );
    rect.setSize( Size( static_cast<float>(charNode.attribute( "w" ).as_int()),
                        static_cast<float>(charNode.attribute( "h" ).as_int()) ) );

    _charRects.emplace( c, rect );
  }
}

void BitmapFont::onRelease() {}
}

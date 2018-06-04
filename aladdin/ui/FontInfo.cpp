#include "FontInfo.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0 ( FontInfo )

FontInfo::FontInfo ( const int fontWeight, const int fontHeight, const bool italic )
{
  _fontWeight = fontWeight;
  _fontHeight = fontHeight;
  _italic = italic;
}

FontInfo::FontInfo ( const FontInfo& fontInfo )
{
  _fontWeight = fontInfo._fontWeight;
  _fontHeight = fontInfo._fontHeight;
  _italic = fontInfo._italic;
}

void FontInfo::setFontWeight ( const int fontWeight )
{
  _fontWeight = fontWeight;
}

void FontInfo::setFontHeight ( const int fontHeight )
{
  _fontHeight = fontHeight;
}

void FontInfo::setItalic ( const bool italic )
{
  _italic = italic;
}

int FontInfo::getFontWeight ( ) const
{
  return _fontWeight;
}

int FontInfo::getFontHeight ( ) const
{
  return _fontHeight;
}

bool FontInfo::getItalic ( ) const
{
  return _italic;
}

bool FontInfo::operator== ( const FontInfo& fontInfo ) const
{
  return (_fontWeight == fontInfo._fontWeight && _fontHeight == fontInfo._fontHeight && _italic == fontInfo._italic);
}

bool FontInfo::operator< ( const FontInfo& fontInfo ) const
{
  if(_fontHeight != fontInfo._fontHeight)
  {
    return _fontHeight < fontInfo._fontHeight;
  }

  if(_fontWeight != fontInfo._fontWeight)
  {
    return _fontWeight < fontInfo._fontWeight;
  }

  return _italic < fontInfo._italic;
}

FontInfo::~FontInfo ( )
{
}
}

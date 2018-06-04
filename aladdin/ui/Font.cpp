#include "Font.h"
#include "../2d/Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 (ala::Font, ala::GameResource)

Font::Font (const std::string& name, const std::string& fontName, const std::string&fontPath, Scene* scope)
  :GameResource ( name, scope )
{
  if(fontPath == "")
  {
    _isSystemFont = true;
    _fontName = fontName;
  }
  else
  {
    _isSystemFont = false;
    TCHAR fullPath[MAX_PATH];
    GetFullPathNameA((fontPath + "/" + fontName).c_str(), MAX_PATH, fullPath, NULL);
    _fileName = fullPath;
    _fontName = fontName.substr ( 0, fontName.find_last_of ( "." ) );
  }
}

ID3DXFont* Font::getDirectXFont ( const FontInfo& fontInfo )
{
  const auto font = _fonts.find(fontInfo);

  if(font == _fonts.end (  ))
  {
    const auto fontResource = Graphics::get (  )->loadDirectXFont(_fontName, fontInfo);
    _fonts[fontInfo] = fontResource;
    return fontResource;
  }
  else
  {
    return font->second;
  }
}

Font::~Font ( )
{
}

void Font::onLoad ( )
{
  if(!_isSystemFont)
  {
    AddFontResourceEx(TEXT(_fileName.c_str()), FR_PRIVATE, NULL);
  }
}

void Font::onRelease ( )
{
  if(!_isSystemFont)
  {
    RemoveFontResourceEx(TEXT (_fileName.c_str()), FR_PRIVATE, NULL);
  }
}
}

#ifndef __ALADDIN_BITMAP_TEXT_H__
#define __ALADDIN_BITMAP_TEXT_H__

#include "BitmapFont.h"
#include "Sprite.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(BitmapText, ala::GameObjectComponent)
private:
  Sprite* _bitmap;
  BitmapFont* _font;
  std::string _text;
  float _characterSpacing;
  int _characterAlignment;
  int _textAlignment;
  bool _visible;
  int _zOrder;

public:
  enum
  {
    TOP,
    BOTTOM,
    CENTER,
    LEFT,
    RIGHT
  };

  BitmapText( GameObject* gameObject, Sprite* bitmap, BitmapFont* font, const std::string& name = "" );

  BitmapText( GameObject* gameObject, const std::string& bitmapName, const std::string& fontName,
              const std::string& name = "" );

  bool isVisible() const;

  void setVisible( const bool val );

  const std::string& getText() const;

  void setText( const std::string& text );

  int getZOrder() const;

  void setZOrder( const int zOrder );

  float getCharacterSpacing() const;

  void setCharacterSpacing( const float characterSpacing );

  int getCharacterAlignment() const;

  void setCharacterAlignment( const int characterAlignment );

  int getTextAlignment() const;

  void setTextAlignment( const int textAlignment );
protected:
  void onRender() override;

private:
  int calculateWorldZOrder() const;
};
}

#endif //!__ALADDIN_BITMAP_TEXT_H__

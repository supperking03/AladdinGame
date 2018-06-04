#ifndef __ALADDIN_BITMAP_FONT_H__
#define __ALADDIN_BITMAP_FONT_H__

#include "2dInclude.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(BitmapFont, ala::GameResource)
private:
  std::string _sourceFile;

  float _charSpaceWidth;
  std::map<char, Rect> _charRects;

public:
  BitmapFont( const std::string& name, const std::string& sourceFile, Scene* sceneScope = NULL );

  const ala::Rect& getCharRect( const char c ) const;
  
  float getCharSpaceWidth() const;

protected:
  void onLoad() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_BITMAP_FONT_H__

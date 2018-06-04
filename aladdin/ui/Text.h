#ifndef __ALADDIN_UI_TEXT_H__
#define __ALADDIN_UI_TEXT_H__

#include "../core/GameObjectComponent.h"
#include "Font.h"
#include "../core/Color.h"

enum {
  ALA_HORIZONTAL_ALIGNMENT_CENTER,
  ALA_HORIZONTAL_ALIGNMENT_LEFT,
  ALA_HORIZONTAL_ALIGNMENT_RIGHT
};

enum {
  ALA_VERTICAL_ALIGNMENT_MIDDLE,
  ALA_VERTICAL_ALIGNMENT_TOP,
  ALA_VERTICAL_ALIGNMENT_BOTTOM
};

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( Text, ala::GameObjectComponent )
private:
  Font* _font;
  FontInfo _fontInfo;

  int _horizontalAlignment;
  int _verticalAlignment;

  Color _textColor;

  std::string _text;
public:
  Text(GameObject* gameObject, const FontInfo& fontInfo, Font* font = NULL, const Color& textColor = Color(255, 255, 255, 255), const int horizontalAlignment = ALA_HORIZONTAL_ALIGNMENT_CENTER, const int verticalAlignment = ALA_VERTICAL_ALIGNMENT_MIDDLE, const std::string& name = "");
  Text(GameObject* gameObject, const FontInfo& fontInfo, const std::string& fontResourceName = "", const Color& textColor = Color(255, 255, 255, 255), const int horizontalAlignment = ALA_HORIZONTAL_ALIGNMENT_CENTER, const int verticalAlignment = ALA_VERTICAL_ALIGNMENT_MIDDLE, const std::string& name = "");

  Font* getFont() const;
  void setFont(Font* font);

  const Color& getTextColor() const;
  void setTextColor(const Color& color);

  const FontInfo& getFontInfo() const;
  void setFontInfo(const FontInfo& fontInfo);

  int getVerticalAlignment() const;
  void setVerticalAlignment(const int verticalAlignment);

  int getHorizontalAlignment() const;
  void setHorizontalAlignment(const int horizontalAlignment);

  const std::string& getText() const;
  void setText(const std::string& text);
protected:
  void onInitialize() override;
  void onRender() override;
  void onRelease() override;
};
}
#endif //!__ALADDIN_UI_TEXT_H__
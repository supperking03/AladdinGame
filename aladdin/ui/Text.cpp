#include "Text.h"
#include "../core/GameManager.h"
#include "../2d/Graphics.h"
#include "RectTransform.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(Text, ala::GameObjectComponent)

Text::Text ( GameObject* gameObject, const FontInfo& fontInfo, Font* font, const Color& textColor, const int horizontalAlignment,
  const int verticalAlignment, const std::string& name )
  : GameObjectComponent ( gameObject, name ),
    _textColor ( textColor )
{
  _fontInfo = fontInfo;
  _horizontalAlignment = horizontalAlignment;
  _verticalAlignment = verticalAlignment;
  _font = font;
}

Text::Text ( GameObject* gameObject, const FontInfo& fontInfo, const std::string& fontResourceName, const Color& textColor, const int horizontalAlignment,
  const int verticalAlignment, const std::string& name )
  : GameObjectComponent(gameObject, name),
    _textColor(textColor)
{
  _fontInfo = fontInfo;
  _horizontalAlignment = horizontalAlignment;
  _verticalAlignment = verticalAlignment;
  _font = static_cast < Font* > ( GameManager::get ( ) -> getResource ( fontResourceName ) );
}

Font* Text::getFont ( ) const
{
  return _font;
}

void Text::setFont ( Font* font )
{
  _font = font;
}

const Color& Text::getTextColor ( ) const
{
  return _textColor;
}

void Text::setTextColor ( const Color& color )
{
  _textColor = color;
}

const FontInfo& Text::getFontInfo ( ) const
{
  return _fontInfo;
}

void Text::setFontInfo ( const FontInfo& fontInfo )
{
  _fontInfo = fontInfo;
}

int Text::getVerticalAlignment ( ) const
{
  return _verticalAlignment;
}

void Text::setVerticalAlignment ( const int verticalAlignment )
{
  _verticalAlignment = verticalAlignment;
}

int Text::getHorizontalAlignment ( ) const
{
  return _horizontalAlignment;
}

void Text::setHorizontalAlignment ( const int horizontalAlignment )
{
  _horizontalAlignment = horizontalAlignment;
}

const std::string& Text::getText ( ) const
{
  return _text;
}

void Text::setText ( const std::string& text )
{
  _text = text;
}

void Text::onInitialize ( )
{
}

void Text::onRender ( )
{
  auto rectTransform = getGameObject()->getComponentT<RectTransform>();

  if(rectTransform == NULL)
  {
    return;
  
  }

  //auto rectTransform = getGameObject()->getTransform();

  auto camera = GameManager::get()->getRunningScene()->getMainCamera();
  auto cameraMatrix = camera->getTransform()->getLocalToWorldMatrix();

  Graphics::get (  )->drawText(_font, _fontInfo, _text, rectTransform->getBoundingRect (), _horizontalAlignment, _verticalAlignment, _textColor, rectTransform->getLocalToWorldMatrix()*Mat4::getRotationZMatrix(360 - camera->getTransform()->getRotation())*cameraMatrix );
}

void Text::onRelease ( )
{
}
}

#ifndef __ALADDIN_EXTRA_RECT_RENDERER_H__
#define __ALADDIN_EXTRA_RECT_RENDERER_H__

#include "ExtraInclude.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(RectRenderer, ala::GameObjectComponent)
private:
  ala::Sprite* _sprite;
  ala::Vec2 _offset;
  ala::Size _size;
  int _alpha;
  int _zOrder;

public:
  RectRenderer(ala::GameObject* gameObject,
    const ala::Vec2& offset, const ala::Size& size, const Color& color,
    const std::string& name = "");

  int getZOrder() const;

  void setZOrder(const int order);

  const ala::Vec2& getOffset() const;

  void setOffset(const ala::Vec2& offset);

  const ala::Size& getSize() const;

  void setSize(const ala::Size& size);

  float getOpacity() const;

  void setOpacity(float opacity);

protected:
  void onRender() override;

private:
  int calculateWorldZOrder() const;
};
}

#endif //!__ALADDIN_EXTRA_RECT_RENDERER_H__

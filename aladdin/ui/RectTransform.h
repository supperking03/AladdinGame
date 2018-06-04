#ifndef __ALADDIN_UI_RECT_TRANSFORM__
#define __ALADDIN_UI_RECT_TRANSFORM__

#include "../core/Transform.h"
#include "../2d/Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( RectTransform, ala::Transform )
private:
  Rect _boundingRect;
public:
  RectTransform(GameObject* gameObject, const Rect& rect, Transform* parentTransform = NULL, const std::string& name = "");
  virtual ~RectTransform();

  const Rect& getBoundingRect() const;
  void setBoundingRect(const Rect& rect);

};
}
#endif //!__ALADDIN_UI_RECT_TRANSFORM__
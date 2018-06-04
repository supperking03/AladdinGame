#include "RectTransform.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::RectTransform, ala::Transform)

RectTransform::RectTransform ( GameObject* gameObject, const Rect& rect, Transform* parentTransform, const std::string& name )
  :Transform ( gameObject, parentTransform, name )
{
  _boundingRect = rect;
}

RectTransform::~RectTransform ( )
{
}

const Rect& RectTransform::getBoundingRect ( ) const
{
  return _boundingRect;
}

void RectTransform::setBoundingRect ( const Rect& rect )
{
  _boundingRect = rect;
}
}

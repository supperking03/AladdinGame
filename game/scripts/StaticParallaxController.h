#ifndef __STATIC_PARALLAX_CONTROLLER_H__
#define __STATIC_PARALLAX_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StaticParallaxController, ala::GameObjectComponent)
private:
  ala::Vec2 _offset;
  float _coef;

  ala::Transform* _selfTransform;

  std::vector<ala::Transform*> _layerTransforms;
  std::vector<float> _layerSizes;

public:
  StaticParallaxController(ala::GameObject* gameObject, const std::string& name = "");

  void setOffset(const ala::Vec2& offset);

  void setCoef(const float speed);

protected:
  void onInitialize() override;

  void onRender() override;
};

#endif //!__STATIC_PARALLAX_CONTROLLER_H__
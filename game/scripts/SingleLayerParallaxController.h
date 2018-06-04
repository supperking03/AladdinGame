#ifndef __SINGLE_LAYER_PARALLAX_CONTROLLER_H__
#define __SINGLE_LAYER_PARALLAX_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SingleLayerParallaxController, ala::GameObjectComponent)
private:
  ala::Vec2 _offset;
  ala::Vec2 _coef;

  ala::Transform* _selfTransform;

public:
  SingleLayerParallaxController(ala::GameObject* gameObject, const std::string& name = "");

  void setOffset(const ala::Vec2& v);

  void setCoef(const ala::Vec2& v);

protected:
  void onInitialize() override;

  void onRender() override;
};

#endif //!__SINGLE_LAYER_PARALLAX_CONTROLLER_H__
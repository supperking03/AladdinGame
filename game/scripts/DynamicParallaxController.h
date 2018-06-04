#ifndef __DYNAMIC_PARALLAX_CONTROLLER_H__
#define __DYNAMIC_PARALLAX_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DynamicParallaxController, ala::GameObjectComponent)
private:
  ala::Vec2 _offset;
  float _coef;
  float _movingSpeed;

  ala::Transform* _selfTransform;

  std::vector<ala::Transform*> _layerTransforms;
  std::vector<float> _layerSizes;
  std::vector<float> _layerMovingOffset;

public:
  DynamicParallaxController(ala::GameObject* gameObject, const std::string& name = "");

  void setOffset(const ala::Vec2& offset);

  void setCoef(const float speed);

  void setMovingSpeed(const float speed);

protected:
  void onInitialize() override;

  void onRender() override;
};

#endif //!__DYNAMIC_PARALLAX_CONTROLLER_H__
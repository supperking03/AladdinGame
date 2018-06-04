#ifndef __ALADDIN_PHYSICS_COLLIDER_RENDERER_H__
#define __ALADDIN_PHYSICS_COLLIDER_RENDERER_H__

#include "PhysicsInclude.h"
#include "Collider.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(ColliderRenderer, ala::GameObjectComponent)
private:
  ala::Collider* _collider;
  ala::Sprite* _redSprite;
  ala::Sprite* _greenSprite;
  ala::Sprite* _blueSprite;
  ala::Sprite* _sprite;
  ala::Color _backColor;
  int _zOrder;

public:
  ColliderRenderer(ala::Collider* collider,
    const float opacity = 0.4f,
    const std::string& name = "");

  int getZOrder() const;

  void setZOrder(const int order);

  void setOpacity(const float opacity);

  float getOpacity() const;

protected:
  void onRender() override;

public:
  void onCollisionEnter(const CollisionInfo& collision) override;
  void onCollisionExit(const CollisionInfo& collision) override;
  void onTriggerEnter(const CollisionInfo& collision) override;
  void onTriggerExit(const CollisionInfo& collision) override;

private:
  int calculateWorldZOrder() const;
};
}

#endif //!__ALADDIN_PHYSICS_COLLIDER_RENDERER_H__

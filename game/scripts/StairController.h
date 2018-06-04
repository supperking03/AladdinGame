#ifndef __STAIR_CONTROLLER_H__
#define __STAIR_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(StairController, ala::GameObjectComponent)
private:
public:
  StairController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~StairController();
void onInitialize() override;
  void onCollisionStay(const ala::CollisionInfo& collision) override;
};

#endif __STAIR_CONTROLLER_H__
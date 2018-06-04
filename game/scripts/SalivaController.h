#ifndef __SALIVA_CONTROLLER_H__
#define __SALIVA_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SalivaController, ala::GameObjectComponent)
public:
  SalivaController(ala::GameObject* gameObject, const std::string &name = "");
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__SALIVA_CONTROLLER_H__

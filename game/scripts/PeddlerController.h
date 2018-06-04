#ifndef __PEDDLER_CONTROLLER_H__
#define __PEDDLER_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(PeddlerController, ala::GameObjectComponent)
protected:


public:
  PeddlerController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~PeddlerController();

  void onTriggerStay(const ala::CollisionInfo& collision) override;
};

#endif __PEDDLER_CONTROLLER_H__
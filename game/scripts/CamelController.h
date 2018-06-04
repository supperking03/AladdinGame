#ifndef __CAMEL_CONTROLLER_H__
#define __CAMEL_CONTROLLER_H__

#include <aladdin.h>


ALA_CLASS_HEADER_1(CamelController, ala::GameObjectComponent)
private:
  bool _collidedWithAladdin;
public:
  CamelController(ala::GameObject* gameObject, const std::string &name = "");
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void onTriggerExit(const ala::CollisionInfo& collision) override;

  void puffSaliva() const;

  bool isCollidedWithAladdin() const;
};

#endif //__CAMEL_CONTROLLER_H__
#ifndef __SPRING_CONTROLLER_H__
#define __SPRING_CONTROLLER_H__

#include <aladdin.h>


ALA_CLASS_HEADER_1(SpringController, ala::GameObjectComponent)
private:
  bool _collidedWithAladdin;
public:
  SpringController(ala::GameObject* gameObject, const std::string &name = "");
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void onTriggerExit(const ala::CollisionInfo& collision) override;

  bool isCollidedWithAladdin() const;
};

#endif //__SPRING_CONTROLLER_H__
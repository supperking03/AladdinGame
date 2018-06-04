#ifndef __ONE_WAY_PLATFORM_CONTROLLER_H__
#define __ONE_WAY_PLATFORM_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(OneWayPlatformController, ala::GameObjectComponent)
private:
  std::map<ala::Collider*, ala::Collider*> _colliders;
public:
  OneWayPlatformController(ala::GameObject* gameObject, const std::string& name = "");
  void addPlatform(ala::Collider* collider);
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void onTriggerExit(const ala::CollisionInfo& collision) override;
};

#endif //!__ONE_WAY_PLATFORM_CONTROLLER_H__
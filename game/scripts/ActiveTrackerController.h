#ifndef __ACTIVE_TRACKER_H__
#define  __ACTIVE_TRACKER_H__

#include <aladdin.h>
ALA_CLASS_HEADER_1(ActiveTrackerController, ala::GameObjectComponent)
private:
  std::vector<ala::Collider*> _colliders;

  bool _isOn;
public:
  ActiveTrackerController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~ActiveTrackerController();

  void onInitialize() override;
  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void addCollider(ala::Collider* collider);

  void turnOff();
  void turnOn();
};

#endif //!#ifndef __ACTIVE_TRACKER_H__
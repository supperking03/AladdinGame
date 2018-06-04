#ifndef __SPELL_TRIGGER_CHECKER__
#define __SPELL_TRIGGER_CHECKER__

#include "core/GameObjectComponent.h"
#include "physics/Rigidbody.h"

ALA_CLASS_HEADER_1(SpellTriggerChecker, ala::GameObjectComponent)
private:
  bool _isCollided;
public:
  bool isCollided() const;

  SpellTriggerChecker(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~SpellTriggerChecker();

  void onTriggerEnter(const ala::CollisionInfo& collision) override;
  void onTriggerStay(const ala::CollisionInfo& collision) override;
  void onTriggerExit(const ala::CollisionInfo& collision) override;
};

#endif //!__COLLISION_CHECKER__

#ifndef __SPELL_CONTROLLER_H__
#define __SPELL_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SpellController, ala::GameObjectComponent)
private:
  bool _colliedWithAladdin;
public:
  SpellController(ala::GameObject* gameObject, const std::string& name = "");

  bool isCollidedWithAladdin() const;

  void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif// __SPELL_CONTROLLER_H__
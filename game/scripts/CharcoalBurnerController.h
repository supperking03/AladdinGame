#ifndef __CHARCOAL_BURNER_CONTROLLER_H__
#define __CHARCOAL_BURNER_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CharcoalBurnerController, ala::GameObjectComponent)
private:
  ala::Timer* _burnTimer;
  ala::Vec2 _burnPosition;

  bool _willBurn;
public:
  CharcoalBurnerController(ala::GameObject* gameObject, const std::string&name = "");

  void onUpdate(const float delta) override;

  void onInitialize() override;

  void onTriggerStay(const ala::CollisionInfo& collision) override;
};

#endif //!__CHARCOAL_BURNER_CONTROLLER_H__

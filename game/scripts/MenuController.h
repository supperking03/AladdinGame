#ifndef __MENU_CONTROLLER__
#define __MENU_CONTROLLER__

#include "core/GameObjectComponent.h"
#include "physics/Rigidbody.h"

ALA_CLASS_HEADER_1(MenuController, ala::GameObjectComponent)
private:
  int _currentIndex;
  ala::Logger _logger;
public:
  MenuController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~MenuController();
  void onInitialize() override;
  void onUpdate(const float delta) override;
};

#endif //!__MENU_CONTROLLER__

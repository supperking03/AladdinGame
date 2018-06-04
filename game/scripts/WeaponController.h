#ifndef __WEAPON_CONTROLLER_H__
#define __WEAPON_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(WeaponController, ala::GameObjectComponent)
private:
  int _damage;
  std::string _type;
public:
  WeaponController(ala::GameObject* gameObject, const std::string & type, const int damage = 0, const std::string& name = "");
  virtual ~WeaponController();

  int getDamage() const;
  const std::string& getType() const;

  void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif //!__WEAPON_CONTROLLER_H__

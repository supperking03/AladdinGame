#ifndef __SWORD_GUARD_PREFAB_H__
#define __SWORD_GUARD_PREFAB_H__

#include <aladdin.h>

class SwordGuardPrefab : ala::Prefab
{
public:
  SwordGuardPrefab()
    : Prefab("Sword Guard") {}


protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //__SWORD_GUARD_PREFAB_H__

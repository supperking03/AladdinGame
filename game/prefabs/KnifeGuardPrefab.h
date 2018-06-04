#ifndef __KNIFE_GUARD_APPLE_PREFAB_H__
#define __KNIFE_GUARD_APPLE_PREFAB_H__
#include <aladdin.h>

class KnifeGuardPrefab : ala::Prefab
{
public:
  KnifeGuardPrefab()
    : Prefab("Knife Guard") {}


protected:
  void doInstantiate(ala::GameObject* object) const override;
};

#endif //__KNIFE_GUARD_APPLE_PREFAB_H__


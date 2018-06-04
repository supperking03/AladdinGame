#ifndef __SNEAKY_PREFAB_H__
#define __SNEAKY_PREFAB_H__

#include <aladdin.h>

class AppleThiefPrefab : ala::Prefab
{
public:
  AppleThiefPrefab()
    : Prefab("Apple Thief") {}


protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //__SNEAKY_PREFAB_H__

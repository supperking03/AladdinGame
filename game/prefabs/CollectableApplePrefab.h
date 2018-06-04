#ifndef __COLLECTABLE_APPLE_PREFAB_H__
#define __COLLECTABLE_APPLE_PREFAB_H__

#include <aladdin.h>

class CollectableApplePrefab : ala::Prefab
{
public:
  CollectableApplePrefab()
    : Prefab("Collectable Apple") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__COLLECTABLE_APPLE_PREFAB_H__

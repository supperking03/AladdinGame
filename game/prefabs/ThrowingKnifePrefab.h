#ifndef __THROWING_KNIFE_PREFAB_H__
#define __THROWING_KNIFE_PREFAB_H__

#include <aladdin.h>

class ThrowingKnifePrefab : ala::Prefab
{
public:
  ThrowingKnifePrefab()
    : Prefab("Throwing Knife") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__THROWING_KNIFE_PREFAB_H__

#ifndef __THROWING_APPLE_PREFAB_H__
#define __THROWING_APPLE_PREFAB_H__

#include <aladdin.h>

class ThrowingApplePrefab : ala::Prefab
{
public:
  ThrowingApplePrefab()
    : Prefab("Throwing Apple") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__THROWING_APPLE_PREFAB_H__

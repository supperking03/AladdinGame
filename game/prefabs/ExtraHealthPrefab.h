#ifndef __EXTRA_HEALTH_PREFAB_H__
#define __EXTRA_HEALTH_PREFAB_H__

#include <aladdin.h>

class ExtraHealthPrefab : ala::Prefab
{
public:
  ExtraHealthPrefab()
    : Prefab("Extra Health") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__EXTRA_HEALTH_PREFAB_H__

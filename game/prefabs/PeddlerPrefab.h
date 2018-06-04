#ifndef __PEDDLER_PREFAB_H__
#define __PEDDLER_PREFAB_H__

#include <aladdin.h>

class PeddlerPrefab : ala::Prefab
{
public:
  PeddlerPrefab()
    : Prefab("Peddler") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__PEDDLER_PREFAB_H__

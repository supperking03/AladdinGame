#ifndef __POT_PREFAB_H__
#define __POT_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class PotPrefab : ala::Prefab
{
public:
  PotPrefab() : Prefab("Pot") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__POT_PREFAB_H__
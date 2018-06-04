#ifndef __JAFAR_FIRE_PREFAB_H__
#define __JAFAR_FIRE_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class JafarFirePrefab : ala::Prefab
{
public:
  JafarFirePrefab() : Prefab("JafarFire") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__JAFAR_FIRE_PREFAB_H__
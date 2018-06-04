#ifndef __BIG_EXPLOSION_PREFAB_H__
#define __BIG_EXPLOSION_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class BigExplosionPrefab : ala::Prefab
{
public:
  BigExplosionPrefab() : Prefab("BigExplosion") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__BIG_EXPLOSION_PREFAB_H__
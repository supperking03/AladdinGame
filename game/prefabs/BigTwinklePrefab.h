#ifndef __BIG_TWINKLE_PREFAB_H__
#define __BIG_TWINKLE_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class BigTwinklePrefab : ala::Prefab
{
public:
  BigTwinklePrefab() : Prefab("BigTwinkle") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__BIG_TWINKLE_PREFAB_H__
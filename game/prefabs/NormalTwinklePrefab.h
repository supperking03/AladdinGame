#ifndef __NORMAL_TWINKLE_PREFAB_H__
#define __NORMAL_TWINKLE_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class NormalTwinklePrefab : ala::Prefab
{
public:
  NormalTwinklePrefab() : Prefab("NormalTwinkle") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__NORMAL_TWINKLE_PREFAB_H__
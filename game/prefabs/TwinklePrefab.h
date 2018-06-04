#ifndef __TWINKLE_PREFAB_H__
#define __TWINKLE_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class TwinklePrefab : ala::Prefab
{
public:
  TwinklePrefab() : Prefab("Twinkle") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__TWINKLE_PREFAB_H__
#ifndef __FALLING_PLATFORM_PREFAB_H__
#define __FALLING_PLATFORM_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class FallingPlatformPrefab : ala::Prefab
{
public:
  FallingPlatformPrefab() : Prefab("FallingPlatform") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__FALLING_PLATFORM_PREFAB_H__
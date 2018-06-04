#ifndef __GENIE_BONUS_PREFAB_H__
#define __GENIE_BONUS_PREFAB_H__

#include <aladdin.h>

class GenieBonusPrefab : ala::Prefab
{
public:
  GenieBonusPrefab()
    : Prefab("Genie Bonus") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__GENIE_BONUS_PREFAB_H__

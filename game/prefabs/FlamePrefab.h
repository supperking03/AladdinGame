#ifndef __FLAME_PREFAB_H__
#define __FLAME_PREFAB_H__

#include <aladdin.h>

class FlamePrefab : public ala::Prefab
{
public:
  FlamePrefab()
    : Prefab("Flame") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__FLAME_PREFAB_H__

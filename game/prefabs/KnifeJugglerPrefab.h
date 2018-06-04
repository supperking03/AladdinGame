#ifndef __KNIFE_JUGGLER_PREFAB_H__
#define __KNIFE_JUGGLER_PREFAB_H__

#include <aladdin.h>

class KnifeJugglerPrefab : ala::Prefab
{
public:
  KnifeJugglerPrefab()
    : Prefab("Knife Juggler") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__KNIFE_JUGGLER_PREFAB_H__

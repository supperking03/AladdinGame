#ifndef __SPEND_THESE_PREFAB_H__
#define __SPEND_THESE_PREFAB_H__

#include <aladdin.h>

class SpendThesePrefab : ala::Prefab
{
public:
  SpendThesePrefab()
    : Prefab("Spend These") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__SPEND_THESE_PREFAB_H__

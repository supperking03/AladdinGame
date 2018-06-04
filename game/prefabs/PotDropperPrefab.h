#ifndef __POT_DROPPER_PREFAB_H__
#define __POT_DROPPER_PREFAB_H__

/*
* Created by kiennm97 on Nov 14th 2017
*/

#include <aladdin.h>


class PotDropperPrefab : public ala::Prefab
{
public:
  PotDropperPrefab() : Prefab("Pot Dropper") {}

  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__POT_DROPPER_PREFAB_H__

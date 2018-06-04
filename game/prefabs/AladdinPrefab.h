#ifndef __ALADDIN_PREFAB_H__
#define __ALADDIN_PREFAB_H__

/*
* Created by kiennm97 on Nov 14th 2017
*/

#include <aladdin.h>


class AladdinPrefab : public ala::Prefab
{
public:
  AladdinPrefab() : Prefab("Aladdin") {}

  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__ALADDIN_PREFAB_H__

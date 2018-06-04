#ifndef __JAFAR_PREFAB_H__
#define __JAFAR_PREFAB_H__

/*
* Created by kiennm97 on Nov 14th 2017
*/

#include <aladdin.h>


class JafarPrefab : public ala::Prefab
{
public:
  JafarPrefab() : Prefab("Jafar") {}

  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__JAFAR_PREFAB_H__

#ifndef __POINTER_PREFAB_H__
#define __POINTER_PREFAB_H__

/*
* Created by kiennm97 on Nov 15th 2017
*/

#include <aladdin.h>

class PointerPrefab : public ala::Prefab {
public:
  PointerPrefab() : Prefab("Pointer") {}

  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__POINTER_PREFAB_H__
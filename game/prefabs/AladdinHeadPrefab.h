#ifndef __ALADDIN_HEAD_PREFAB_H__
#define __ALADDIN_HEAD_PREFAB_H__

#include <aladdin.h>

class AladdinHeadPrefab : ala::Prefab
{
public:
  AladdinHeadPrefab()
    : Prefab("Aladdin Head") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__ALADDIN_HEAD_PREFAB_H__

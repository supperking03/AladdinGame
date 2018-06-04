#ifndef __ABU_HEAD_PREFAB_H__
#define __ABU_HEAD_PREFAB_H__

#include <aladdin.h>

class AbuHeadPrefab : ala::Prefab
{
public:
  AbuHeadPrefab()
    : Prefab("Abu Head") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__ABU_HEAD_PREFAB_H__

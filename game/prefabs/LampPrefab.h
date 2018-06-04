#ifndef __LAMP_PREFAB_H__
#define __LAMP_PREFAB_H__

#include <aladdin.h>

class LampPrefab : ala::Prefab
{
public:
  LampPrefab()
    : Prefab("Lamp") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__LAMP_PREFAB_H__

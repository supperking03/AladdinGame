#ifndef __STAFF_GUARD_PREFAB_H__
#define __STAFF_GUARD_PREFAB_H__

#include <aladdin.h>

class StaffGuardPrefab : ala::Prefab
{
public:
  StaffGuardPrefab()
    : Prefab("Staff Guard") {}


protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //__STAFF_GUARD_PREFAB_H__

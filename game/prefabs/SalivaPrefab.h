#ifndef __SALIVA_PREFAB_H__
#define __SALIVA_PREFAB_H__

#include <aladdin.h>

class SalivaPrefab : public ala::Prefab
{
public:
  SalivaPrefab() : Prefab("Saliva") {}

  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__SALIVA_PREFAB_H__
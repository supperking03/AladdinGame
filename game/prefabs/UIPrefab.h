#ifndef __UI_PREFAB_H__
#define __UI_PREFAB_H__

#include <aladdin.h>

class UIPrefab: public ala::Prefab
{
public:
  UIPrefab() : Prefab("Aladdin UI") {}

  void doInstantiate(ala::GameObject* object) const override;

};

#endif //!__UI_PREFAB_H__

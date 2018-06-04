#ifndef __PEDDLER_TEXT_PREFAB_H__
#define __PEDDLER_TEXT_PREFAB_H__

#include <aladdin.h>

class PeddlerTextPrefab : ala::Prefab
{
public:
  PeddlerTextPrefab()
    : Prefab("Peddler Text") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__PEDDLER_TEXT_PREFAB_H__

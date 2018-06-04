#ifndef __LEVEL_COMPLETE_PREFAB_H__
#define __LEVEL_COMPLETE_PREFAB_H__

#include <aladdin.h>

class LevelCompletePrefab : ala::Prefab
{
public:
  LevelCompletePrefab()
    : Prefab("Level Complete") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__LEVEL_COMPLETE_PREFAB_H__

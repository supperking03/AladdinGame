#ifndef __CHECKPOINT_PREFAB_H__
#define __CHECKPOINT_PREFAB_H__

#include <aladdin.h>

class CheckpointPrefab : ala::Prefab
{
public:
  CheckpointPrefab()
    : Prefab("Checkpoint") {}

protected:
  void doInstantiate(ala::GameObject* object) const override;
};


#endif //!__CHECKPOINT_PREFAB_H__

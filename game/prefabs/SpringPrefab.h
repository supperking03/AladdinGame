#ifndef __SPRING_PREFAB_H__
#define __SPRING_PREFAB_H__

#include <aladdin.h>

class SpringPrefab: public ala::Prefab
{
public:
  SpringPrefab(): Prefab("Spring") {}
  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__SPRING_PREFAB_H__
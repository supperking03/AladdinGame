
#ifndef __SAND_PREFAB_H__
#define __SAND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SandPrefab, ala::PrefabV2)
public:
  SandPrefab()
    : PrefabV2("Sand") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__SAND_PREFAB_H__
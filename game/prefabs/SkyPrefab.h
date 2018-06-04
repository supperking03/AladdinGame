
#ifndef __SKY_PREFAB_H__
#define __SKY_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SkyPrefab, ala::PrefabV2)
public:
  SkyPrefab()
    : PrefabV2("Sky") {}

private:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__SKY_PREFAB_H__
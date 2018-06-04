#ifndef __FADE_IN_EFFECT_PREFAB_H__
#define __FADE_IN_EFFECT_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(FadeInEffectPrefab, ala::PrefabV2)
public:
  FadeInEffectPrefab()
    : PrefabV2("Fade In Effect") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__FADE_IN_EFFECT_PREFAB_H__
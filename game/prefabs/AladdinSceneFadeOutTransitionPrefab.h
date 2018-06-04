#ifndef __ALADDIN_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#define __ALADDIN_SCENE_FADE_OUT_TRANSITION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(AladdinSceneFadeOutTransitionPrefab, ala::PrefabV2)
public:
  AladdinSceneFadeOutTransitionPrefab()
    : PrefabV2("Aladdin Scene Fade Out Transition") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__ALADDIN_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
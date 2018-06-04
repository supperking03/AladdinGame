#ifndef __COMPLETE_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#define __COMPLETE_SCENE_FADE_OUT_TRANSITION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CompleteSceneFadeOutTransitionPrefab, ala::PrefabV2)
public:
  CompleteSceneFadeOutTransitionPrefab()
    : PrefabV2("Compelete Scene Fade Out Transition") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__COMPLETE_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#ifndef __DIE_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#define __DIE_SCENE_FADE_OUT_TRANSITION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(DieSceneFadeOutTransitionPrefab, ala::PrefabV2)
public:
  DieSceneFadeOutTransitionPrefab()
    : PrefabV2("Die Scene Fade Out Transition") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__DIE_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
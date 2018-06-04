#ifndef __RETRY_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#define __RETRY_SCENE_FADE_OUT_TRANSITION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(RetrySceneFadeOutTransitionPrefab, ala::PrefabV2)
public:
  RetrySceneFadeOutTransitionPrefab()
    : PrefabV2("Retry Scene Fade Out Transition") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__RETRY_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
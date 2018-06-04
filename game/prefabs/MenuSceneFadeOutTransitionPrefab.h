#ifndef __MENU_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
#define __MENU_SCENE_FADE_OUT_TRANSITION_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(MenuSceneFadeOutTransitionPrefab, ala::PrefabV2)
public:
  MenuSceneFadeOutTransitionPrefab()
    : PrefabV2("Menu Scene Fade Out Transition") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__MENU_SCENE_FADE_OUT_TRANSITION_PREFAB_H__
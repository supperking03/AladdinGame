#ifndef __PLAY_MENU_PREFAB_H__
#define __PLAY_MENU_PREFAB_H__
#include "../../aladdin/core/Prefab.h"

class PlayMenuPrefab : ala::Prefab
{
public:
  PlayMenuPrefab() : Prefab("Play Menu") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__PLAY_MENU_PREFAB_H__
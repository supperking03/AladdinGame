#ifndef __OPTION_MENU_PREFAB_H__
#define __OPTION_MENU_PREFAB_H__
#include "../../aladdin/core/Prefab.h"

class OptionMenuPrefab : ala::Prefab
{
public:
  OptionMenuPrefab() : Prefab("Option Menu") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__OPTION_MENU_PREFAB_H__
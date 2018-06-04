#ifndef __JAFAR_SPELL_PREFAB_H__
#define __JAFAR_SPELL_PREFAB_H__

#include "../../aladdin/core/Prefab.h"

class JafarSpellPrefab : ala::Prefab
{
public:
  JafarSpellPrefab() : Prefab("JafarSpell") {}

  void doInstantiate(ala::GameObject* object) const override;


};

#endif //!__JAFAR_SPELL_PREFAB_H__
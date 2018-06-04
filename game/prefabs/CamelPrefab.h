#ifndef __CAMEL_PREFAB_H__
#define __CAMEL_PREFAB_H__

#include <aladdin.h>

class CamelPrefab: public ala::Prefab
{
public:
  CamelPrefab() : Prefab("Camel") {}

  void doInstantiate(ala::GameObject* object) const override;

};

#endif !//__CAMEL_PREFAB_H__

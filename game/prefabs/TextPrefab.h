#ifndef __TEXT_PREFAB_H__
#define __TEXT_PREFAB_H__

#include <aladdin.h>

class TextPrefab : public ala::Prefab {
public:
  TextPrefab() : Prefab("Text") {}

  void doInstantiate(ala::GameObject* object) const override;
};

#endif //!__TEXT_PREFAB_H__

#ifndef __EDITOR_PREFAB_H__
#define __EDITOR_PREFAB_H__

#include <aladdin.h>

class EditorPrefab : public ala::Prefab {
public:
  EditorPrefab() : Prefab("Editor") {}

  void doInstantiate(ala::GameObject * object) const override;
};

#endif //!__EDITOR_PREFAB_H__

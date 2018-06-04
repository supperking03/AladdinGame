#ifndef __JAFAR_FOREGROUND_PREFAB_H__
#define __JAFAR_FOREGROUND_PREFAB_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(JafarForegroundPrefab, ala::PrefabV2)
public:
  JafarForegroundPrefab()
    : PrefabV2("Jafar Foreground") {}

protected:
  void doInstantiate(ala::GameObject* object, std::istringstream& argsStream) const override;
};

#endif //!__JAFAR_FOREGROUND_PREFAB_H__
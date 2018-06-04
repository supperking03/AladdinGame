#include "EditorPrefab.h"
#include "../scripts/EditorController.h"

USING_NAMESPACE_ALA;

void EditorPrefab::doInstantiate(ala::GameObject * object) const {
  auto controller = new EditorController(object);
}

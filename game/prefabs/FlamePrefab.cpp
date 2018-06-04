#include "FlamePrefab.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../Macros.h"

USING_NAMESPACE_ALA;

void FlamePrefab::doInstantiate(ala::GameObject* object) const {
  // components
  new SpriteRenderer(object, "jafar.png");

  const auto animator = new Animator(object, "fire", "jafar.anm");

  const auto stateManager = new StateManager(object, "fire");

  new Rigidbody(object, PhysicsMaterial(1.f, 0.f), ALA_BODY_TYPE_DYNAMIC);
  const auto collider = new Collider(object, true, Vec2(0, 0), Size(23, 46), 1, 0);
  collider->setTag(ENEMY_WEAPON_TAG);

  new WeaponController(object, WEAPON_TYPE_ENEMY_FLAME, 1);

  // states
  new State(stateManager, "fire",
    NULL,
    [=](float dt) {
    if (!animator->isPlaying()) {
      object->release();
    }
  },
    NULL);

  // configurations
  object->setLayer("Foreground");
}

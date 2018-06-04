#include "SalivaPrefab.h"
#include "../Macros.h"
#include "../scripts/WeaponController.h"
#include "../scripts/SalivaController.h"
#include "../Macros.h"

void SalivaPrefab::doInstantiate(ala::GameObject* object) const
{
  new ala::SpriteRenderer(object, "camel.png");

  new ala::Animator(object, "saliva", "camel.anm");

  const auto body = new ala::Rigidbody(object, ala::PhysicsMaterial(), ALA_BODY_TYPE_DYNAMIC, 0.0f);

  const auto collider = new ala::Collider(object, true, ala::Vec2(0, 0), ala::Size(9, 9));
  collider->setTag(ALADDIN_WEAPON_TAG);
  collider->ignoreTag(NPC_TAG);
  collider->ignoreTag(ALADDIN_WEAPON_TAG);
  collider->ignoreTag(ALADDIN_TAG);
  collider->ignoreTag(ROPE_CHECKER_TAG);
  collider->ignoreTag(ROPE_TAG);
  collider->ignoreTag(COLLECTABLE_ITEM_TAG);
  collider->ignoreTag(ENEMY_WEAPON_TAG);
  collider->ignoreTag(HANGER_TAG);
  collider->ignoreTag(HANGER_CHECKER_TAG);
  collider->ignoreTag(MAP_BLOCKER_TAG);

  new WeaponController(object, WEAPON_TYPE_ALADDIN_SALIVA, 1);

  object->setLayer("Foreground");

  new ala::ColliderRenderer(collider);

  body->setVelocity(ala::Vec2(300.f, body->getVelocity().getY()));

  new SalivaController(object);
}

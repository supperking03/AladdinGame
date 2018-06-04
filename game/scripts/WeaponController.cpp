#include "WeaponController.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(WeaponController, ala::GameObjectComponent)

WeaponController::WeaponController(ala::GameObject* gameObject, const std::string & type, const int damage, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _damage(damage),
  _type(type)
{
}

WeaponController::~WeaponController()
{
}

int WeaponController::getDamage() const
{
  return _damage;
}

const std::string& WeaponController::getType() const
{
  return _type;
}

void WeaponController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  const auto selfCollider = collision.getColliderA()->getGameObject() == getGameObject() ? collision.getColliderA() : collision.getColliderB();
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject() ? collision.getColliderB() : collision.getColliderA();
  const auto selfWeapon = selfCollider->getGameObject()->getComponentT<WeaponController>();
  const auto otherWeapon = otherCollider->getGameObject()->getComponentT<WeaponController>();

  if(selfWeapon == NULL || otherWeapon == NULL)
  {
    return;
  }

  if(selfWeapon->getType() == WEAPON_TYPE_ALADDIN_APPLE)
  {
    if(otherWeapon->getType() == WEAPON_TYPE_ENEMY_KNIFE)
    {
      selfCollider->getGameObject()->getComponentT<ala::StateManager>()->changeState("apple_half");
      otherCollider->getGameObject()->release();
    }
    if(otherWeapon->getType() == WEAPON_TYPE_ENEMY_SWORD && otherCollider->getTag() == ENEMY_WEAPON_TAG)
    {
      selfCollider->getGameObject()->getComponentT<ala::StateManager>()->changeState("apple_half");
    }
  }

  if(selfWeapon->getType() == WEAPON_TYPE_ENEMY_KNIFE)
  {
    if (otherWeapon->getType() == WEAPON_TYPE_ALADDIN_SWORD && otherCollider->getTag() == ALADDIN_WEAPON_TAG)
    {
      selfCollider->setTag(ALADDIN_WEAPON_TAG);
      selfCollider->unignoreTag(ENEMY_TAG);
      selfCollider->ignoreTag(ALADDIN_TAG);
      selfWeapon->_type = WEAPON_TYPE_ALADDIN_KNIFE;
      const auto knifeBody = selfCollider->getGameObject()->getComponentT<ala::Rigidbody>();
      knifeBody->setVelocity(ala::Vec2(-knifeBody->getVelocity().getX()/2.f, 300));
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("SwordChing.wav"));
    }
  }

  if (selfWeapon->getType() == WEAPON_TYPE_ENEMY_SWORD && selfCollider->getTag() == ENEMY_WEAPON_TAG)
  {
    if (otherWeapon->getType() == WEAPON_TYPE_ALADDIN_SWORD && otherCollider->getTag() == ALADDIN_WEAPON_TAG)
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("SwordChing.wav"));
    }
  }
}

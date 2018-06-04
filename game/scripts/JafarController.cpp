#include "JafarController.h"
#include "physics/CollisionInfo.h"
#include "2d/Animator.h"
#include "physics/Rigidbody.h"
#include "../Macros.h"
#include "WeaponController.h"
#include "../GameData.h"
#include "../scenes/CompleteScene.h"
#include "../Macros.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(JafarController, EnemyController)

JafarController::JafarController(ala::GameObject* gameObject, const int health,
  const std::function<int(WeaponController*)> damageCalculator, const std::string& name)
  : EnemyController(gameObject, health, damageCalculator, name),
  _spawnTimer(NULL),
  _turnTimer(NULL),
  _shoot(0),
  _stateManager(NULL),
  _health(health),
  _transform(NULL),
  _aladdinStateManager(NULL)
{
  _turnTimer = new ala::Timer(getGameObject());
  _spawnTimer = new ala::Timer(getGameObject());
}

JafarController::~JafarController()
{
}

void JafarController::onInitialize()
{
  _aladdinStateManager = ala::GameManager::get()->getObjectByTag(ALADDIN_TAG)->getComponentT<ala::StateManager>();
  _transform = getGameObject()->getTransform();
  _stateManager = getGameObject()->getComponentT<ala::StateManager>();
  _spawnTimer->start(0.1);
  _turnTimer->start(1.6);
  GameData::get()->setInt(APPLE_DATA_KEY, 10);
}

void JafarController::onUpdate(const float delta)
{
  if(_turnTimer->isDone())
  {
    _shoot++;
    if(_shoot%2 == 0)
    {
      _turnTimer->start(1.6);
    }
    else
    {
      if (_health > 13)
      {
        _stateManager->changeState("jafar_idle");
      }     
      _turnTimer->start(1.5);
    }
  }

  if (_spawnTimer->isDone() && _shoot % 2 != 0 && _health > 13)
  {
    _stateManager->changeState("jafar_idle");
  }

  if (_spawnTimer->isDone() && _shoot%2 == 0 && _stateManager->getCurrentStateName() == "jafar_fire")
  { 
    const auto aladdin = ala::GameManager::get()->getObjectByName("Aladdin")->getTransform();
    getGameObject()->getTransform()->setScaleX((aladdin->getPositionX() - getGameObject()->getTransform()->getPositionX())/abs(aladdin->getPositionX() - getGameObject()->getTransform()->getPositionX()));
    auto shot = ala::GameManager::get()->getPrefab("JafarSpell")->instantiate("fire1");
    shot->getTransform();
    shot->getTransform()->setPosition(getGameObject()->getTransform()->getPosition());
    
    _spawnTimer->start(0.1);
  }
  if(_stateManager->getCurrentStateName() == "snake" && !ala::GameManager::get()->getObjectByTag(JAFAR_TAG)->getComponentT<ala::Animator>()->isPlaying() && ala::GameManager::get()->getObjectByTag(JAFAR_TAG)->getComponentT<ala::Animator>()->getActionName() == "snake")
  {
    _stateManager->changeState("snake");

    const auto aladdin = ala::GameManager::get()->getObjectByName("Aladdin")->getTransform();
    auto shot = ala::GameManager::get()->getPrefab("JafarFire")->instantiate("fire1");
    shot->getTransform()->setPosition(getGameObject()->getTransform()->getPosition());
    

    if (aladdin->getPositionX() > getGameObject()->getTransform()->getPositionX())
    {
      shot->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(100, 0));
      getGameObject()->getTransform()->setScaleX(1);
    }
    else
    {
      shot->getComponentT<ala::Rigidbody>()->setVelocity(ala::Vec2(-100, 0));
      shot->getTransform()->setScaleX(-1);
      getGameObject()->getTransform()->setScaleX(-1);
    }
  }
}

void JafarController::onTriggerEnter(const ala::CollisionInfo& collision)
{
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
    ? collision.getColliderB()
    : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  const auto selfCollider = collision.getColliderA() == otherCollider
    ? collision.getColliderB()
    : collision.getColliderA();

  if (selfCollider->getTag() == ENEMY_WEAPON_TAG)
  {
    if ((otherCollider->getTag() == ALADDIN_WEAPON_TAG)) {
      onHit(otherCollider->getGameObject()->getComponentT<WeaponController>());
    }
  }
}

void JafarController::onOutOfHealth() const
{
  ala::GameManager::get()->getPrefabV2("Complete Scene Fade Out Transition")->instantiate();
}

void JafarController::onHit(WeaponController* weaponController)
{
  if (weaponController->getType() == WEAPON_TYPE_ALADDIN_SWORD)
  {
    _aladdinStateManager->changeState("spin-jafar");
    return;
  }

  _health -= _damageCalculator(weaponController);

  if (weaponController->getType() == WEAPON_TYPE_ALADDIN_APPLE && _health > 0)
  {
    ala::GameManager::get()->getPrefab("BigExplosion")->instantiate(weaponController->getGameObject()->getTransform()->getPosition());
    weaponController->getGameObject()->releaseInNextFrame();
  }

  if (_health <= 13 && _stateManager->getCurrentStateName() != "snake"  && _health > 0)
  {
    _stateManager->changeState("snake");
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("GenieFumes.wav"));
  }

  if (_health <= 0)
  {
    onOutOfHealth();
  }
}

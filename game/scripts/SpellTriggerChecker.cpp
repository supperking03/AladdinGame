#include "SpellTriggerChecker.h"

#include "physics/CollisionInfo.h"
#include "extra/MoveBy.h"

ALA_CLASS_SOURCE_1(SpellTriggerChecker, GameObjectComponent)


bool SpellTriggerChecker::isCollided() const
{
  return _isCollided;
}

SpellTriggerChecker::SpellTriggerChecker(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _isCollided(false)
{
}

SpellTriggerChecker::~SpellTriggerChecker()
{
}

void SpellTriggerChecker::onTriggerEnter(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getName() == "Aladdin" || collision.getColliderB()->getName() == "Aladdin")
  {
    _isCollided = true;
    auto actionManager = new ala::ActionManager(ala::GameManager::get()->getObjectByName("Aladdin"));
    auto moveBy = new ala::MoveBy(ala::Vec2(-15, 0), 0.1);
    actionManager->addAction(moveBy);
  }
}

void SpellTriggerChecker::onTriggerStay(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getName() == "Aladdin" || collision.getColliderB()->getName() == "Aladdin")
  {
    //_isCollided = true;
  }
}

void SpellTriggerChecker::onTriggerExit(const ala::CollisionInfo& collision)
{
  if (collision.getColliderA()->getName() == "Aladdin" || collision.getColliderB()->getName() == "Aladdin")
  {
    _isCollided = false;
  }
}


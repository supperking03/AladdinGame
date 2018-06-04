#include "CharcoalBurnerController.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(CharcoalBurnerController, ala::GameObjectComponent)

CharcoalBurnerController::CharcoalBurnerController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _burnTimer(NULL),
  _burnPosition(0,0),
  _willBurn(false)
{
}

void CharcoalBurnerController::onUpdate(const float delta)
{
  if(_burnTimer->isDone() && _willBurn)
  {
    ala::GameManager::get()->getGlobalMessenger()->broadcast(PLAY_SFX_MESSAGE, new ala::StringMessageArgs("FireFromCoal.wav"));
    _willBurn = false;
    ala::GameManager::get()->getPrefab("Flame")->instantiate(_burnPosition);
  }
}

void CharcoalBurnerController::onInitialize()
{
  _burnTimer = getGameObject()->getComponentT<ala::Timer>();
}

void CharcoalBurnerController::onTriggerStay(const ala::CollisionInfo& collision)
{
  if(collision.getColliderA()->getTag() == ALADDIN_TAG && !_willBurn)
  {
    if(collision.getNormal().getY() != -1)
    {
      return;
    }
    _willBurn = true;
    _burnTimer->start(0.25f);
    _burnPosition = ala::Vec2(collision.getColliderA()->getGameObject()->getTransform()->getPositionX(), collision.getColliderB()->getBoundingRect().getMidY() + 15);
  }
  else if(collision.getColliderB()->getTag() == ALADDIN_TAG&& !_willBurn)
  {
    if (collision.getNormal().getY() != 1)
    {
      return;
    }
    _willBurn = true;
    _burnTimer->start(0.25f);
    _burnPosition = ala::Vec2(collision.getColliderB()->getGameObject()->getTransform()->getPositionX(), collision.getColliderA()->getBoundingRect().getMidY() + 15);
  }
}

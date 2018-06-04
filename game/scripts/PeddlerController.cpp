#include "PeddlerController.h"
#include "../Macros.h"
#include "../arguments/IntArg.h"
#include "../GameData.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_1(PeddlerController, ala::GameObjectComponent)

PeddlerController::PeddlerController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name)
{
}

PeddlerController::~PeddlerController()
{
}

void PeddlerController::onTriggerStay(const ala::CollisionInfo& collision)
{
  if (((collision.getColliderA()->getTag() == ALADDIN_TAG || collision.getColliderB()->getTag() == ALADDIN_TAG) &&
    (collision.getColliderA()->getTag() == SHOP_5_TAG || collision.getColliderB()->getTag() == SHOP_5_TAG) && (ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW))))
  {
    if(GameData::get()->getInt(RUBY_DATA_KEY) >= 5)
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(RUBY_LOST_MESSAGE, new IntArg(5));
      ala::GameManager::get()->getGlobalMessenger()->broadcast(LIVES_ACQUIRED_MESSAGE, new IntArg(1));
      return;
    }
    else
    {
      ala::GameManager::get()->getPrefab("Peddler Text")->instantiate(ala::GameManager::get()->getRunningScene()->getMainCamera());
    }
  }
  if (((collision.getColliderA()->getTag() == ALADDIN_TAG || collision.getColliderB()->getTag() == ALADDIN_TAG) &&
    (collision.getColliderA()->getTag() == SHOP_10_TAG || collision.getColliderB()->getTag() == SHOP_10_TAG) && (ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW))))
  {
    if (GameData::get()->getInt(RUBY_DATA_KEY) >= 10)
    {
      ala::GameManager::get()->getGlobalMessenger()->broadcast(RUBY_LOST_MESSAGE, new IntArg(10));
    }
    else
    {
      ala::GameManager::get()->getPrefab("Peddler Text")->instantiate(ala::GameManager::get()->getRunningScene()->getMainCamera());
    }
  }
}


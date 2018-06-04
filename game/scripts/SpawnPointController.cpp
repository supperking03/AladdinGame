#include "SpawnPointController.h"
#include "../Macros.h"
#include "../arguments/IntArg.h"
#include "CollectableItemController.h"

ALA_CLASS_SOURCE_1(SpawnPointController, ala::GameObjectComponent)

SpawnPointController::SpawnPointController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _value(""),
  _object("") 
{
}

SpawnPointController::~SpawnPointController()
{
}

void SpawnPointController::setId(const int id)
{
  _id = id;
}

int SpawnPointController::getId() const
{
  return _id;
}


void SpawnPointController::setValue(const std::string& value)
{
  _value = value;
}

const std::string& SpawnPointController::getValue() const
{
  return _value;
}

void SpawnPointController::setObject(const string& object)
{
  _object = object;
}

void SpawnPointController::spawnItem() const
{
  if(canSpawn())
  {
    auto item = ala::GameManager::get()->getPrefab(_object)->instantiate(getGameObject());
    item->getComponentT<CollectableItemController>()->setValue(_value);
  }
}

bool SpawnPointController::canSpawn() const
{
  return getGameObject()->getTransform()->getChildren().size() == 0;
}




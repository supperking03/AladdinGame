#include "SpawnGroupController.h"
#include "../Macros.h"
#include "../arguments/IntArg.h"
#include "../Macros.h"

ALA_CLASS_SOURCE_2(SpawnGroupController, ala::GameObjectComponent, ala::MessageListener)

SpawnGroupController::SpawnGroupController(ala::GameObject* gameObject, const std::string& name)
  :GameObjectComponent(gameObject, name),
  _id(0)
{
}

SpawnGroupController::~SpawnGroupController()
{
}

void SpawnGroupController::spawn()
{
  for (auto i:_points)
  {
    i->spawnItem();
  }
}

void SpawnGroupController::addSpawnPoint(SpawnPointController* point)
{
  _points.push_back(point);
}

void SpawnGroupController::setId(const int id)
{
  _id = id;
}

int SpawnGroupController::getId() const
{
  return _id;
}

void SpawnGroupController::onInitialize()
{
  subscribeGlobalMessage(SPAWN_APPLE_MESSAGE,[=] (ala::MessageArgs* message)
  {
    int id = static_cast<IntArg*>(message)->getPayload();
    for(auto point: _points)
    {
      if(!point->canSpawn())
      {
        return;
      }
    }
    for (auto point : _points)
    {
      if (point->getId() == id)
      {
        point->spawnItem();
      }
    }
  });
}



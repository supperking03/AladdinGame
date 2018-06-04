#ifndef __SPAWN_GROUP_CONTROLLER_H__
#define __SPAWN_GROUP_CONTROLLER_H__

#include <aladdin.h>
#include "SpawnPointController.h"

ALA_CLASS_HEADER_2(SpawnGroupController, ala::GameObjectComponent, ala::MessageListener)
protected:
  vector<SpawnPointController*> _points;
  int _id;
public:
  SpawnGroupController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~SpawnGroupController();
  void spawn();
  void addSpawnPoint(SpawnPointController* point);
  void setId(const int id);
  int getId() const;
  void onInitialize() override;
};

#endif __SPAWN_GROUP_CONTROLLER_H__
#ifndef __SPAWN_POINT_CONTROLLER_H__
#define __SPAWN_POINT_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(SpawnPointController, ala::GameObjectComponent)
protected:
  string _value;
  string _object;
  int _id;

public:
  SpawnPointController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~SpawnPointController();
  void setValue(const std::string& value);
  const std::string& getValue() const;
  void setObject(const string& object);
  void spawnItem() const;

  void setId(const int id);
  int getId() const;

  bool canSpawn() const;
};

#endif __SPAWN_POINT_CONTROLLER_H__
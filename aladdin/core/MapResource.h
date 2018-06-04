#ifndef __ALADDIN_CORE_MAP_RESOURCE_H__
#define __ALADDIN_CORE_MAP_RESOURCE_H__

#include "CoreMacros.h"
#include "GameResource.h"
#include "MapObject.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(MapResource, ala::GameResource)
  // ======================================
  // Basic
  // ======================================
private:
  std::string _sourceFile;
  std::map<std::string, std::string> _properties;
  std::map<std::string, std::vector<MapObject>> _objects;
public:
  MapResource(const std::string& name, const std::string& sourceFile, Scene* scope = NULL);

  virtual ~MapResource();

  const std::string& getSourceFile() const;

  std::vector<MapObject>& getMapObjects(const std::string& objectGroupName);

  const std::map<std::string, std::vector<MapObject>>& getAllObjects() const;

  int getIntProperty(const std::string& key);
  float getFloatProperty(const std::string& key);
  std::string getStringProperty(const std::string& key);

  bool keyExist(const std::string& key);

protected:
  void onLoad() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_CORE_MAP_RESOURCE_H__

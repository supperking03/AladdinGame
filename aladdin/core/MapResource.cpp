#include "MapResource.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(MapResource, ala::GameResource)

MapResource::MapResource(const std::string& name, const std::string& sourceFile, Scene* scope)
  :GameResource(name, scope)
{
  _sourceFile = sourceFile;
}

MapResource::~MapResource()
{
}

const std::string& MapResource::getSourceFile() const
{
  return _sourceFile;
}

std::vector<MapObject>& MapResource::getMapObjects(const std::string& objectGroupName) 
{
  return _objects[objectGroupName];
}

const std::map<std::string, std::vector<MapObject>>& MapResource::getAllObjects() const
{
  return _objects;
}

int MapResource::getIntProperty(const std::string& key)
{
  return stoi(_properties[key]);
}

float MapResource::getFloatProperty(const std::string& key)
{
  return stof(_properties[key]);
}

std::string MapResource::getStringProperty(const std::string& key)
{
  return _properties[key];
}

bool MapResource::keyExist(const std::string& key)
{
  return _properties.find(key) != _properties.end();
}

void MapResource::onLoad()
{
  pugi::xml_document _mapFile;
  pugi::xml_parse_result result = _mapFile.load_file(_sourceFile.c_str());

  ALA_ASSERT(result);

  auto mapNode = _mapFile.child("map");
  auto propertiesNode = mapNode.child("properties");
  auto objectGroups = mapNode.children("objectgroup");

  const auto width = mapNode.attribute("tilewidth").as_float();
  const auto height = mapNode.attribute("tileheight").as_float();

  for(auto objectGroup: objectGroups)
  {
    const auto name = objectGroup.attribute("name").as_string();

    for(auto object: objectGroup.children("object"))
    {
      const float x = object.attribute("x").as_float() + object.attribute("width").as_float() *0.5f - width /2.f ;
      const float y = ( -object.attribute("y").as_float() - object.attribute("height").as_float()*1.5f +    height /2.f);
      const auto objectRect = Rect(Vec2(x, y), object.attribute("width").as_float(), object.attribute("height").as_float());

      _objects[name].push_back(MapObject(object.attribute("name").as_string(), object.attribute("type").as_string(), objectRect, object.child("properties").children()));
    }
  }

  for(auto mapProperty: propertiesNode.children())
  {
    _properties[mapProperty.attribute("name").as_string()] = mapProperty.attribute("value").as_string();
  }
}

void MapResource::onRelease()
{
}
}

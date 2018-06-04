#include "MapObject.h"
#include "../2d/Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(MapObject)

MapObject::MapObject(const std::string &name, const std::string &type, const Rect& objectRect, const pugi::xml_object_range<pugi::xml_node_iterator>& properties)
  :_name(name),
    _type(type),
    _objectRect(objectRect)
{
  for(auto property: properties)
  {
    _properties[property.attribute("name").as_string()] = property.attribute("value").as_string();
  }
}

MapObject::~MapObject()
{
}

int MapObject::getInt(const std::string& key)
{
  return std::stoi(_properties[key]);
}

float MapObject::getFloat(const std::string& key)
{
  return std::stof(_properties[key]);
}

std::string MapObject::getString(const std::string& key)
{
  return _properties[key];
}

bool MapObject::keyExist(const std::string& key) const
{
  return _properties.find(key) != _properties.end();
}

const Rect& MapObject::getRect() const
{
  return _objectRect;
}

const std::string& MapObject::getName() const
{
  return _name;
}

const std::string& MapObject::getType() const
{
  return _type;
}
}

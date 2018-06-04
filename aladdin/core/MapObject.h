#ifndef __ALADDIN_CORE_MAP_OBJECT_H__
#define __ALADDIN_CORE_MAP_OBJECT_H__

#include "ClassMeta.h"
#include "CoreMacros.h"
#include "../pugixml/pugixml.hpp"
#include "../2d/Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(MapObject)
private:
  std::map<std::string, std::string> _properties;

  std::string _name;
  std::string _type;
  Rect _objectRect;
public:
  MapObject(const std::string &name, const std::string &type, const Rect& objectRect, const pugi::xml_object_range<pugi::xml_node_iterator>& properties);
  virtual ~MapObject();
  int getInt(const std::string& key);
  float getFloat(const std::string& key);
  std::string getString(const std::string& key);

  bool keyExist(const std::string& key) const;

  const Rect &getRect() const;

  const std::string &getName() const;
  const std::string &getType() const;
};
}

#endif //!__ALADDIN_CORE_MAP_OBJECT_H__

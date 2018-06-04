#ifndef __COLLECTABLE_ITEM_CONTROLLER_H__
#define __COLLECTABLE_ITEM_CONTROLLER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_1(CollectableItemController, ala::GameObjectComponent)
protected:
  string _value;
  bool _collidedWithAladdin;
public:
  CollectableItemController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~CollectableItemController();
  void setValue(const std::string& value);
  const std::string& getValue() const;

  bool isCollidedWithAladdin() const;

  void onTriggerEnter(const ala::CollisionInfo& collision) override;
};

#endif __COLLECTABLE_ITEM_CONTROLLER_H__
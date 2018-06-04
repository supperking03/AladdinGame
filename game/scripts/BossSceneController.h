#ifndef __BOSS_SCENE_CONTROLLER_H__
#define __BOSS_SCENE_CONTROLLER_H__

#include <aladdin.h>
#include "BossSceneController.h"
#include "CharcoalBurnerController.h"

ALA_CLASS_HEADER_2(BossSceneController, ala::GameObjectComponent, ala::MessageListener)
protected:
  vector<ala::Collider*> _charcoalBurners;
  ala::Transform* _aladdin;
  ala::Transform* _jafar;
  //int _id;
public:
  BossSceneController(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~BossSceneController();

  void onInitialize() override;
  void onUpdate(const float delta) override;
};

#endif __BOSS_SCENE_CONTROLLER_H__
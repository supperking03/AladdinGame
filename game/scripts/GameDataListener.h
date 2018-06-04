#ifndef __GAME_DATA_LISTENER_H__
#define __GAME_DATA_LISTENER_H__

#include <aladdin.h>

ALA_CLASS_HEADER_2(GameDataListener, ala::GameObjectComponent, ala::MessageListener)
private:
public:
  GameDataListener(ala::GameObject* gameObject, const std::string& name = "");
  virtual ~GameDataListener();
void onInitialize() override;
};

#endif __GAME_DATA_LISTENER_H__
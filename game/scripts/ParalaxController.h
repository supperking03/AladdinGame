#ifndef __PARALAX_CONTROLLER_H__
#define __PARALAX_CONTROLLER_H__

/*
* Created by kiennm97 on Oct 15th 2017
*/

#include <aladdin.h>
NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(ParalaxController, ala::GameObjectComponent)
int _speedLayer;
int _speedPlayer;
bool _isStatic;
int _startX;
int _startY;

public:
  ParalaxController(ala::GameObject* gameObject, const std::string& name = "");





  bool getIsStatic();

  void setIsStatic(const bool isStatic);

  int getSpeedLayer();

  void setSpeedLayer(const int speedLayer);

  int getSpeedPlayer();

  void setSpeedPlayer(const int speedPlayer);


protected:
  void onInitialize() override;

  void onUpdate(const float delta) override;

  void onRelease() override;
};
}

#endif //!__LAYER_CONTROLLER_H__
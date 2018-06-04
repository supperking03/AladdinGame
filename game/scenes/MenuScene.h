#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__
/*
*
*/

#include <aladdin.h>

class MenuScene : public ala::Scene, public ala::MessageListener {
public:
  MenuScene();

protected:
  void onPreInitialize() override;

  void onPostInitialize() override;

  void onPreRelease() override;
};

#endif //!__MENU_SCENE_H__

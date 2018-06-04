#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__
/*
*
*/

#include <aladdin.h>

class DieScene : public ala::Scene {
public:
  DieScene(const std::string & lastMap);

protected:
  void onPreInitialize() override;
  void onPreRelease() override;

private:
  std::string _lastMap;
};

#endif //!__BOSS_SCENE_H__

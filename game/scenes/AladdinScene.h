#ifndef __ALADDIN_SCENE_H__
#define __ALADDIN_SCENE_H__

/*
* Created by kiennm97 on Nov 14th 2017
*/

#include <aladdin.h>

class AladdinScene : public ala::Scene {
public:
  AladdinScene(const std::string &mapResourceName);

  const std::string& getMapResourceName() const;
protected:
  void onPreInitialize() override;

  void onPostInitialize() override;

  void onPreRelease() override;
private:
  std::string _mapResourceName;
  std::string _backgroundMusicResourceName;
};

#endif //!__ALADDIN_SCENE_H__
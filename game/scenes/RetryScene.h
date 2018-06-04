#ifndef __RETRY_SCENE_H__
#define __RETRY_SCENE_H__
/*
*
*/

#include <aladdin.h>

class RetryScene : public ala::Scene {
public:
  RetryScene(const std::string & lastMap);
protected:
  void onPreInitialize() override;
  void onPostUpdate(const float delta) override;
  void onPreRelease() override;
  void onPostInitialize() override;

private:
  std::string _lastMap;
};

#endif //!__RETRY_SCENE_H__

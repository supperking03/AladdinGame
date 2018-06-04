#ifndef __COMPLETE_SCENE_H__
#define __COMPLETE_SCENE_H__
/*
*
*/

#include <aladdin.h>

class CompleteScene : public ala::Scene{
public:
  CompleteScene();

protected:
  void onPreInitialize() override;
  void onPostUpdate(const float delta) override;
  void onPreRelease() override;
  void onPostInitialize() override;

private:
};

#endif //!__COMPLETE_SCENE_H__

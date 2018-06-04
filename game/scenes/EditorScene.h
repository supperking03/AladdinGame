#ifndef __EDITOR_SCENE_H__
#define __EDITOR_SCENE_H__
/*
*
*/

#include <aladdin.h>

class EditorScene : public ala::Scene, public ala::MessageListener {
public:
  EditorScene();

protected:
  void onPreInitialize() override;

  void onPreRelease() override;

private:
  ala::Logger _logger;
};

#endif //!__EDITOR_SCENE_H__

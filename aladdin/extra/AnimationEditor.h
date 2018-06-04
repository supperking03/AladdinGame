#ifndef __ALADDIN_EXTRA_ANIMATION_EDITOR_H__
#define __ALADDIN_EXTRA_ANIMATION_EDITOR_H__

#include "ExtraInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1( AnimationEditor, ala::GameObjectComponent)
private:
  ala::Logger _logger;
  std::string _actionName;

public:
  AnimationEditor( ala::GameObject* gameObject, const std::string& actionName, const std::string& name = "" );

protected:
  bool onPreInitialize() override;

  void onUpdate( const float delta ) override;
};
}

#endif //!__ALADDIN_EXTRA_ANIMATION_EDITOR_H__

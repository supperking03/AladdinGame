#ifndef __ANIMATION_EXAMPLE_PREFAB_H__
#define __ANIMATION_EXAMPLE_PREFAB_H__

#include <aladdin.h>

class AnimationAndStateExamplePrefab : public ala::Prefab
{
public:
  AnimationAndStateExamplePrefab() : Prefab( "Animation And State Example" ) {}

  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__ANIMATION_EXAMPLE_PREFAB_H__

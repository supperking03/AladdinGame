#ifndef __BALL_PREFAB_H__
#define __BALL_PREFAB_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include <aladdin.h>

class BasicExamplePrefab : public ala::Prefab
{
public:
  BasicExamplePrefab(): Prefab( "Basic Example" ) {}
   
  void doInstantiate( ala::GameObject* object ) const override;
};

#endif //!__BALL_PREFAB_H__

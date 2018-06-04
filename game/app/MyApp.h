#ifndef __MY_APP_H__
#define __MY_APP_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include <aladdin.h>

class MyApp : public ala::Application {
public:
  MyApp();

protected:
  void onPreInitialize() override;

  void onPostInitialize() override;
};

#endif //!__MY_APP_H__

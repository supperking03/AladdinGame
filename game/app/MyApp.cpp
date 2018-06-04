#include "MyApp.h"
#include "MyResourceInitializer.h"
#include "../scenes/AladdinScene.h"
#include "../scenes/EditorScene.h"
#include "../scenes/MenuScene.h"
#include "../scenes/CompleteScene.h"
#include "../scenes/RetryScene.h"

USING_NAMESPACE_ALA;

MyApp::MyApp() : Application() {}

void MyApp::onPreInitialize() {
  // configurations
  setResolutionSize(640/2, 460/2);
  setScreenSize(320 * 3, 230 * 3);
  setTitle( "Aladdin - Team Cau Vong" );

  setFps( 60 );
  Logger::setLogLevel( ALA_LOG_INFO );

  // resource initializers
  registerResourceInitializer( new MyResourceInitializer() );
}

void MyApp::onPostInitialize() {
  // starter scene
  startWithScene( new MenuScene() );
}

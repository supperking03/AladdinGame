#include "MyApp.h"

#ifndef LOG_STREAM
#define LOG_STREAM 1
#endif

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow ) {
  MyApp* app = new MyApp();
  app->run( hInstance,
            hPrevInstance,
            lpCmdLine,
            nCmdShow,
            LOG_STREAM );
  app->release();

  if ( LOG_STREAM == 1 ) {
    system( "pause" );
  }
  return 0;
}

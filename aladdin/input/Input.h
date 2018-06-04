#ifndef __ALADDIN_INPUT_INPUT_H__
#define __ALADDIN_INPUT_INPUT_H__

#include "InputInclude.h"

enum {
  ALA_KEY_NONE,
  ALA_KEY_BACKSPACE,
  ALA_KEY_DELETE,
  ALA_KEY_TAB,
  ALA_KEY_RETURN,
  ALA_KEY_ESCAPE,
  ALA_KEY_SPACE,
  ALA_KEY_KEYPAD_0,
  ALA_KEY_KEYPAD_1,
  ALA_KEY_KEYPAD_2,
  ALA_KEY_KEYPAD_3,
  ALA_KEY_KEYPAD_4,
  ALA_KEY_KEYPAD_5,
  ALA_KEY_KEYPAD_6,
  ALA_KEY_KEYPAD_7,
  ALA_KEY_KEYPAD_8,
  ALA_KEY_KEYPAD_9,
  ALA_KEY_KEYPAD_PERIOD,
  ALA_KEY_KEYPAD_DIVIDE,
  ALA_KEY_KEYPAD_MULTIPLY,
  ALA_KEY_KEYPAD_MINUS,
  ALA_KEY_KEYPAD_PLUS,
  ALA_KEY_KEYPAD_ENTER,
  ALA_KEY_KEYPAD_EQUALS,
  ALA_KEY_UP_ARROW,
  ALA_KEY_DOWN_ARROW,
  ALA_KEY_LEFT_ARROW,
  ALA_KEY_RIGHT_ARROW,
  ALA_KEY_INSERT,
  ALA_KEY_HOME,
  ALA_KEY_END,
  ALA_KEY_PAGE_UP,
  ALA_KEY_PAGE_DOWN,
  ALA_KEY_F1,
  ALA_KEY_F2,
  ALA_KEY_F3,
  ALA_KEY_F4,
  ALA_KEY_F5,
  ALA_KEY_F6,
  ALA_KEY_F7,
  ALA_KEY_F8,
  ALA_KEY_F9,
  ALA_KEY_F10,
  ALA_KEY_F11,
  ALA_KEY_F12,
  ALA_KEY_F13,
  ALA_KEY_F14,
  ALA_KEY_F15,
  ALA_KEY_ALPHA_0,
  ALA_KEY_ALPHA_1,
  ALA_KEY_ALPHA_2,
  ALA_KEY_ALPHA_3,
  ALA_KEY_ALPHA_4,
  ALA_KEY_ALPHA_5,
  ALA_KEY_ALPHA_6,
  ALA_KEY_ALPHA_7,
  ALA_KEY_ALPHA_8,
  ALA_KEY_ALPHA_9,
  ALA_KEY_COMMA,
  ALA_KEY_MINUS,
  ALA_KEY_PERIOD,
  ALA_KEY_SLASH,
  ALA_KEY_COLON,
  ALA_KEY_SEMICOLON,
  ALA_KEY_EQUALS,
  ALA_KEY_LEFTBRACKET,
  ALA_KEY_BACKSLASH,
  ALA_KEY_RIGHTBRACKET,
  ALA_KEY_A,
  ALA_KEY_B,
  ALA_KEY_C,
  ALA_KEY_D,
  ALA_KEY_E,
  ALA_KEY_F,
  ALA_KEY_G,
  ALA_KEY_H,
  ALA_KEY_I,
  ALA_KEY_J,
  ALA_KEY_K,
  ALA_KEY_L,
  ALA_KEY_M,
  ALA_KEY_N,
  ALA_KEY_O,
  ALA_KEY_P,
  ALA_KEY_Q,
  ALA_KEY_R,
  ALA_KEY_S,
  ALA_KEY_T,
  ALA_KEY_U,
  ALA_KEY_V,
  ALA_KEY_W,
  ALA_KEY_X,
  ALA_KEY_Y,
  ALA_KEY_Z,
  ALA_KEY_NUM_LOCK,
  ALA_KEY_CAPS_LOCK,
  ALA_KEY_RIGHT_SHIFT,
  ALA_KEY_LEFT_SHIFT,
  ALA_KEY_RIGHT_CONTROL,
  ALA_KEY_LEFT_CONTROL,
  ALA_KEY_RIGHT_ALT,
  ALA_KEY_LEFT_ALT,
  ALA_KEY_RIGHT_WINDOWS,
  ALA_KEY_LEFT_WINDOWS,
  __ALA_KEY_END,
};

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Input, ala::Initializable, ala::Releasable)
  // =====================================================
  // Basics
  // =====================================================

  friend class Application;

private:
  static Input* __instance;
  Logger _logger;

public:
  static Input* get();

  Input();

  virtual ~Input();

  bool getKey( const int code ) const;

  bool getKeyDown( const int code ) const;

  bool getKeyUp( const int code ) const;

  bool getKey( const std::string& keyName ) const;

  bool getKeyDown( const std::string& keyName ) const;

  bool getKeyUp( const std::string& keyName ) const;

  bool getMouseButton( int button ) const;

  bool getMouseButtonDown( int button ) const;

  bool getMouseButtonUp( int button ) const;

  bool anyKey() const;

  bool anyKeyDown() const;

  Vec2 getMousePosition() const;

  bool isMousePresent() const;

  std::string getInputString() const;

public:
  void initialize() override;

  void release() override;

  void update();

  void onBackgroundToForeground();

  // =================================================
  // Platform specific
  // =================================================

private:
  HINSTANCE _hInstance;
  HWND _hWnd;
  LPDIRECTINPUT8 _directXInput;
  LPDIRECTINPUTDEVICE8 _directXInputKeyboard;
  char _directXKeys[256];
  char _oldDirectXKeys[256];
  std::map<int, int> _directXKeysMapInt;
  std::map<std::string, int> _directXKeysMapString;

  void initDirectXInput();

  void initDirectXKeysMap();

  void releaseDirectXInput();

  bool directXKeyDown( const int key ) const;

  bool oldDirectXKeyDown( const int key ) const;

  int toDirectXKey( const int code ) const;

  int toDirectXKey( const std::string& keyName ) const;
};
}

#endif //!__ALADDIN_INPUT_INPUT_H__

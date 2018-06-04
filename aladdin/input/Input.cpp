#include "Input.h"

/*
 * Created by phuctm97 on Oct 1st 2017
 */

NAMESPACE_ALA
{
// =====================================================
// Basics
// =====================================================

ALA_CLASS_SOURCE_2( ala::Input, ala::Initializable, ala::Releasable)

Input* Input::__instance( NULL );

Input* Input::get() {
  if ( __instance == NULL ) {
    __instance = new Input();
  }
  return __instance;
}

Input::Input()
  : _logger( "ala::Input" ),
    _directXInput( 0 ),
    _directXInputKeyboard( 0 ) {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));
  _logger.info( "Created" );
}

Input::~Input() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
  _logger.info( "Released" );
}

bool Input::getKey( const int code ) const {
  return directXKeyDown( toDirectXKey( code ) );
}

bool Input::getKeyDown( const int code ) const {
  const auto directXKey = toDirectXKey( code );
  return directXKeyDown( directXKey ) && (!oldDirectXKeyDown( directXKey ));
}

bool Input::getKeyUp( const int code ) const {
  const auto directXKey = toDirectXKey( code );
  return (!directXKeyDown( directXKey )) && oldDirectXKeyDown( directXKey );
}

bool Input::getKey( const std::string& keyName ) const {
  return directXKeyDown( toDirectXKey( keyName ) );
}

bool Input::getKeyDown( const std::string& keyName ) const {
  const auto directXKey = toDirectXKey( keyName );
  return directXKeyDown( directXKey ) && (!oldDirectXKeyDown( directXKey ));
}

bool Input::getKeyUp( const std::string& keyName ) const {
  const auto directXKey = toDirectXKey( keyName );
  return (!directXKeyDown( directXKey )) && oldDirectXKeyDown( directXKey );
}

bool Input::getMouseButton( int button ) const {
  throw "Not implemented";
}

bool Input::getMouseButtonDown( int button ) const {
  throw "Not implemented";
}

bool Input::getMouseButtonUp( int button ) const {
  throw "Not implemented";
}

bool Input::anyKey() const {
  for ( auto code = 0; code < __ALA_KEY_END; ++code ) {
    if ( getKey( code ) ) return true;
  }
  return false;
}

bool Input::anyKeyDown() const {
  for ( auto code = 0; code < __ALA_KEY_END; ++code ) {
    if ( getKeyDown( code ) ) return true;
  }
  return false;
}

Vec2 Input::getMousePosition() const {
  throw "Not implemented";
}

bool Input::isMousePresent() const {
  throw "Not implemented";
}

std::string Input::getInputString() const {
  throw "Not implemented";
}

void Input::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  initDirectXInput();

  initDirectXKeysMap();

  setToInitialized();
}

void Input::release() {
  ALA_ASSERT(isInitialized() && (!isReleased()) && (!isReleasing()));

  setToReleasing();

  releaseDirectXInput();

  setToReleased();

  // destroy
  delete this;
}

void Input::update() {
  // refresh last frame keys
  std::copy( _directXKeys, _directXKeys + 256, _oldDirectXKeys );
  _directXInputKeyboard->GetDeviceState( sizeof(_directXKeys), static_cast<LPVOID>(&_directXKeys) );
}

void Input::onBackgroundToForeground() {
  if ( !isInitialized() ) return;
  if ( _directXInputKeyboard->Poll() != DI_OK ) {
    if ( _directXInputKeyboard->Acquire() == DI_OK ) {
      _logger.info( "Acquired Keyboard Device" );
    }
  }
}


// =================================================
// Platform specific
// =================================================

void Input::initDirectXInput() {
  HRESULT result;

  // init DirectX Input
  result = DirectInput8Create(
    _hInstance,
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    reinterpret_cast<void**>(&_directXInput),
    NULL );
  ALA_ASSERT(!FAILED(result));

  _logger.info( "Created DirectX Input" );

  // init DirectX Input Keyboard
  result = _directXInput->CreateDevice( GUID_SysKeyboard, &_directXInputKeyboard, NULL );
  ALA_ASSERT(!FAILED(result));

  _logger.info( "Created DirectX Input Keyboard Device" );

  // acquire Keyboard
  result = _directXInputKeyboard->SetDataFormat( &c_dfDIKeyboard );
  ALA_ASSERT(result == DI_OK);
  result = _directXInputKeyboard->SetCooperativeLevel( _hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
  ALA_ASSERT(result == DI_OK);
  result = _directXInputKeyboard->Acquire();
  ALA_ASSERT(result == DI_OK);

  _logger.info( "Acquired Keyboard Device" );
}

void Input::initDirectXKeysMap() {
  _directXKeysMapInt.emplace( ALA_KEY_NONE, 0 );
  _directXKeysMapInt.emplace( ALA_KEY_BACKSPACE, DIK_BACKSPACE );
  _directXKeysMapInt.emplace( ALA_KEY_DELETE, DIK_DELETE );
  _directXKeysMapInt.emplace( ALA_KEY_TAB, DIK_TAB );
  _directXKeysMapInt.emplace( ALA_KEY_RETURN, DIK_RETURN );
  _directXKeysMapInt.emplace( ALA_KEY_ESCAPE, DIK_ESCAPE );
  _directXKeysMapInt.emplace( ALA_KEY_SPACE, DIK_SPACE );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_0, DIK_NUMPAD0 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_1, DIK_NUMPAD1 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_2, DIK_NUMPAD2 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_3, DIK_NUMPAD3 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_4, DIK_NUMPAD4 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_5, DIK_NUMPAD5 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_6, DIK_NUMPAD6 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_7, DIK_NUMPAD7 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_8, DIK_NUMPAD8 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_9, DIK_NUMPAD9 );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_PERIOD, DIK_NUMPADPERIOD );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_DIVIDE, DIK_NUMPADSLASH );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_MULTIPLY, DIK_NUMPADSTAR );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_MINUS, DIK_NUMPADMINUS );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_PLUS, DIK_NUMPADPLUS );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_ENTER, DIK_NUMPADENTER );
  _directXKeysMapInt.emplace( ALA_KEY_KEYPAD_EQUALS, DIK_NUMPADEQUALS );
  _directXKeysMapInt.emplace( ALA_KEY_UP_ARROW, DIK_UPARROW );
  _directXKeysMapInt.emplace( ALA_KEY_DOWN_ARROW, DIK_DOWNARROW );
  _directXKeysMapInt.emplace( ALA_KEY_LEFT_ARROW, DIK_LEFTARROW );
  _directXKeysMapInt.emplace( ALA_KEY_RIGHT_ARROW, DIK_RIGHTARROW );
  _directXKeysMapInt.emplace( ALA_KEY_INSERT, DIK_INSERT );
  _directXKeysMapInt.emplace( ALA_KEY_HOME, DIK_HOME );
  _directXKeysMapInt.emplace( ALA_KEY_END, DIK_END );
  _directXKeysMapInt.emplace( ALA_KEY_PAGE_UP, DIK_PGUP );
  _directXKeysMapInt.emplace( ALA_KEY_PAGE_DOWN, DIK_PGDN );
  _directXKeysMapInt.emplace( ALA_KEY_F1, DIK_F1 );
  _directXKeysMapInt.emplace( ALA_KEY_F2, DIK_F2 );
  _directXKeysMapInt.emplace( ALA_KEY_F3, DIK_F3 );
  _directXKeysMapInt.emplace( ALA_KEY_F4, DIK_F4 );
  _directXKeysMapInt.emplace( ALA_KEY_F5, DIK_F5 );
  _directXKeysMapInt.emplace( ALA_KEY_F6, DIK_F6 );
  _directXKeysMapInt.emplace( ALA_KEY_F7, DIK_F7 );
  _directXKeysMapInt.emplace( ALA_KEY_F8, DIK_F8 );
  _directXKeysMapInt.emplace( ALA_KEY_F9, DIK_F9 );
  _directXKeysMapInt.emplace( ALA_KEY_F10, DIK_F10 );
  _directXKeysMapInt.emplace( ALA_KEY_F11, DIK_F11 );
  _directXKeysMapInt.emplace( ALA_KEY_F12, DIK_F12 );
  _directXKeysMapInt.emplace( ALA_KEY_F13, DIK_F13 );
  _directXKeysMapInt.emplace( ALA_KEY_F14, DIK_F14 );
  _directXKeysMapInt.emplace( ALA_KEY_F15, DIK_F15 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_0, DIK_0 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_1, DIK_1 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_2, DIK_2 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_3, DIK_3 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_4, DIK_4 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_5, DIK_5 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_6, DIK_6 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_7, DIK_7 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_8, DIK_8 );
  _directXKeysMapInt.emplace( ALA_KEY_ALPHA_9, DIK_9 );
  _directXKeysMapInt.emplace( ALA_KEY_COMMA, DIK_COMMA );
  _directXKeysMapInt.emplace( ALA_KEY_MINUS, DIK_MINUS );
  _directXKeysMapInt.emplace( ALA_KEY_PERIOD, DIK_PERIOD );
  _directXKeysMapInt.emplace( ALA_KEY_SLASH, DIK_SLASH );
  _directXKeysMapInt.emplace( ALA_KEY_COLON, DIK_COLON );
  _directXKeysMapInt.emplace( ALA_KEY_SEMICOLON, DIK_SEMICOLON );
  _directXKeysMapInt.emplace( ALA_KEY_EQUALS, DIK_EQUALS );
  _directXKeysMapInt.emplace( ALA_KEY_LEFTBRACKET, DIK_LBRACKET );
  _directXKeysMapInt.emplace( ALA_KEY_BACKSLASH, DIK_BACKSLASH );
  _directXKeysMapInt.emplace( ALA_KEY_RIGHTBRACKET, DIK_RBRACKET );
  _directXKeysMapInt.emplace( ALA_KEY_A, DIK_A );
  _directXKeysMapInt.emplace( ALA_KEY_B, DIK_B );
  _directXKeysMapInt.emplace( ALA_KEY_C, DIK_C );
  _directXKeysMapInt.emplace( ALA_KEY_D, DIK_D );
  _directXKeysMapInt.emplace( ALA_KEY_E, DIK_E );
  _directXKeysMapInt.emplace( ALA_KEY_F, DIK_F );
  _directXKeysMapInt.emplace( ALA_KEY_G, DIK_G );
  _directXKeysMapInt.emplace( ALA_KEY_H, DIK_H );
  _directXKeysMapInt.emplace( ALA_KEY_I, DIK_I );
  _directXKeysMapInt.emplace( ALA_KEY_J, DIK_J );
  _directXKeysMapInt.emplace( ALA_KEY_K, DIK_K );
  _directXKeysMapInt.emplace( ALA_KEY_L, DIK_L );
  _directXKeysMapInt.emplace( ALA_KEY_M, DIK_M );
  _directXKeysMapInt.emplace( ALA_KEY_N, DIK_N );
  _directXKeysMapInt.emplace( ALA_KEY_O, DIK_O );
  _directXKeysMapInt.emplace( ALA_KEY_P, DIK_P );
  _directXKeysMapInt.emplace( ALA_KEY_Q, DIK_Q );
  _directXKeysMapInt.emplace( ALA_KEY_R, DIK_R );
  _directXKeysMapInt.emplace( ALA_KEY_S, DIK_S );
  _directXKeysMapInt.emplace( ALA_KEY_T, DIK_T );
  _directXKeysMapInt.emplace( ALA_KEY_U, DIK_U );
  _directXKeysMapInt.emplace( ALA_KEY_V, DIK_V );
  _directXKeysMapInt.emplace( ALA_KEY_W, DIK_W );
  _directXKeysMapInt.emplace( ALA_KEY_X, DIK_X );
  _directXKeysMapInt.emplace( ALA_KEY_Y, DIK_Y );
  _directXKeysMapInt.emplace( ALA_KEY_Z, DIK_Z );
  _directXKeysMapInt.emplace( ALA_KEY_NUM_LOCK, DIK_NUMLOCK );
  _directXKeysMapInt.emplace( ALA_KEY_CAPS_LOCK, DIK_CAPSLOCK );
  _directXKeysMapInt.emplace( ALA_KEY_RIGHT_SHIFT, DIK_RSHIFT );
  _directXKeysMapInt.emplace( ALA_KEY_LEFT_SHIFT, DIK_LSHIFT );
  _directXKeysMapInt.emplace( ALA_KEY_RIGHT_CONTROL, DIK_RCONTROL );
  _directXKeysMapInt.emplace( ALA_KEY_LEFT_CONTROL, DIK_LCONTROL );
  _directXKeysMapInt.emplace( ALA_KEY_RIGHT_ALT, DIK_RALT );
  _directXKeysMapInt.emplace( ALA_KEY_LEFT_ALT, DIK_LALT );
  _directXKeysMapInt.emplace( ALA_KEY_RIGHT_WINDOWS, DIK_RWIN );
  _directXKeysMapInt.emplace( ALA_KEY_LEFT_WINDOWS, DIK_LWIN );

  _directXKeysMapString.emplace( "", 0 );
  _directXKeysMapString.emplace( "backspace", DIK_BACKSPACE );
  _directXKeysMapString.emplace( "delete", DIK_DELETE );
  _directXKeysMapString.emplace( "tab", DIK_TAB );
  _directXKeysMapString.emplace( "return", DIK_RETURN );
  _directXKeysMapString.emplace( "esc", DIK_ESCAPE );
  _directXKeysMapString.emplace( "space", DIK_SPACE );
  _directXKeysMapString.emplace( "[0]", DIK_NUMPAD0 );
  _directXKeysMapString.emplace( "[1]", DIK_NUMPAD1 );
  _directXKeysMapString.emplace( "[2]", DIK_NUMPAD2 );
  _directXKeysMapString.emplace( "[3]", DIK_NUMPAD3 );
  _directXKeysMapString.emplace( "[4]", DIK_NUMPAD4 );
  _directXKeysMapString.emplace( "[5]", DIK_NUMPAD5 );
  _directXKeysMapString.emplace( "[6]", DIK_NUMPAD6 );
  _directXKeysMapString.emplace( "[7]", DIK_NUMPAD7 );
  _directXKeysMapString.emplace( "[8]", DIK_NUMPAD8 );
  _directXKeysMapString.emplace( "[9]", DIK_NUMPAD9 );
  _directXKeysMapString.emplace( "[.]", DIK_NUMPADPERIOD );
  _directXKeysMapString.emplace( "[/]", DIK_NUMPADSLASH );
  _directXKeysMapString.emplace( "[*]", DIK_NUMPADSTAR );
  _directXKeysMapString.emplace( "[-]", DIK_NUMPADMINUS );
  _directXKeysMapString.emplace( "[+]", DIK_NUMPADPLUS );
  _directXKeysMapString.emplace( "[enter]", DIK_NUMPADENTER );
  _directXKeysMapString.emplace( "[=]", DIK_NUMPADEQUALS );
  _directXKeysMapString.emplace( "up", DIK_UPARROW );
  _directXKeysMapString.emplace( "down", DIK_DOWNARROW );
  _directXKeysMapString.emplace( "left", DIK_LEFTARROW );
  _directXKeysMapString.emplace( "right", DIK_RIGHTARROW );
  _directXKeysMapString.emplace( "insert", DIK_INSERT );
  _directXKeysMapString.emplace( "home", DIK_HOME );
  _directXKeysMapString.emplace( "end", DIK_END );
  _directXKeysMapString.emplace( "page up", DIK_PGUP );
  _directXKeysMapString.emplace( "page down", DIK_PGDN );
  _directXKeysMapString.emplace( "f1", DIK_F1 );
  _directXKeysMapString.emplace( "f2", DIK_F2 );
  _directXKeysMapString.emplace( "f3", DIK_F3 );
  _directXKeysMapString.emplace( "f4", DIK_F4 );
  _directXKeysMapString.emplace( "f5", DIK_F5 );
  _directXKeysMapString.emplace( "f6", DIK_F6 );
  _directXKeysMapString.emplace( "f7", DIK_F7 );
  _directXKeysMapString.emplace( "f8", DIK_F8 );
  _directXKeysMapString.emplace( "f9", DIK_F9 );
  _directXKeysMapString.emplace( "f10", DIK_F10 );
  _directXKeysMapString.emplace( "f11", DIK_F11 );
  _directXKeysMapString.emplace( "f12", DIK_F12 );
  _directXKeysMapString.emplace( "f13", DIK_F13 );
  _directXKeysMapString.emplace( "f14", DIK_F14 );
  _directXKeysMapString.emplace( "f15", DIK_F15 );
  _directXKeysMapString.emplace( "0", DIK_0 );
  _directXKeysMapString.emplace( "1", DIK_1 );
  _directXKeysMapString.emplace( "2", DIK_2 );
  _directXKeysMapString.emplace( "3", DIK_3 );
  _directXKeysMapString.emplace( "4", DIK_4 );
  _directXKeysMapString.emplace( "5", DIK_5 );
  _directXKeysMapString.emplace( "6", DIK_6 );
  _directXKeysMapString.emplace( "7", DIK_7 );
  _directXKeysMapString.emplace( "8", DIK_8 );
  _directXKeysMapString.emplace( "9", DIK_9 );
  _directXKeysMapString.emplace( ",", DIK_COMMA );
  _directXKeysMapString.emplace( "-", DIK_MINUS );
  _directXKeysMapString.emplace( ".", DIK_PERIOD );
  _directXKeysMapString.emplace( "/", DIK_SLASH );
  _directXKeysMapString.emplace( ":", DIK_COLON );
  _directXKeysMapString.emplace( ";", DIK_SEMICOLON );
  _directXKeysMapString.emplace( "=", DIK_EQUALS );
  _directXKeysMapString.emplace( "[", DIK_LBRACKET );
  _directXKeysMapString.emplace( "\\", DIK_BACKSLASH );
  _directXKeysMapString.emplace( "]", DIK_RBRACKET );
  _directXKeysMapString.emplace( "a", DIK_A );
  _directXKeysMapString.emplace( "b", DIK_B );
  _directXKeysMapString.emplace( "c", DIK_C );
  _directXKeysMapString.emplace( "d", DIK_D );
  _directXKeysMapString.emplace( "e", DIK_E );
  _directXKeysMapString.emplace( "f", DIK_F );
  _directXKeysMapString.emplace( "g", DIK_G );
  _directXKeysMapString.emplace( "h", DIK_H );
  _directXKeysMapString.emplace( "i", DIK_I );
  _directXKeysMapString.emplace( "j", DIK_J );
  _directXKeysMapString.emplace( "k", DIK_K );
  _directXKeysMapString.emplace( "l", DIK_L );
  _directXKeysMapString.emplace( "m", DIK_M );
  _directXKeysMapString.emplace( "n", DIK_N );
  _directXKeysMapString.emplace( "o", DIK_O );
  _directXKeysMapString.emplace( "p", DIK_P );
  _directXKeysMapString.emplace( "q", DIK_Q );
  _directXKeysMapString.emplace( "r", DIK_R );
  _directXKeysMapString.emplace( "s", DIK_S );
  _directXKeysMapString.emplace( "t", DIK_T );
  _directXKeysMapString.emplace( "u", DIK_U );
  _directXKeysMapString.emplace( "v", DIK_V );
  _directXKeysMapString.emplace( "w", DIK_W );
  _directXKeysMapString.emplace( "x", DIK_X );
  _directXKeysMapString.emplace( "y", DIK_Y );
  _directXKeysMapString.emplace( "z", DIK_Z );
  _directXKeysMapString.emplace( "num lock", DIK_NUMLOCK );
  _directXKeysMapString.emplace( "caps lock", DIK_CAPSLOCK );
  _directXKeysMapString.emplace( "right shift", DIK_RSHIFT );
  _directXKeysMapString.emplace( "left shift", DIK_LSHIFT );
  _directXKeysMapString.emplace( "right ctrl", DIK_RCONTROL );
  _directXKeysMapString.emplace( "left ctrl", DIK_LCONTROL );
  _directXKeysMapString.emplace( "right alt", DIK_RALT );
  _directXKeysMapString.emplace( "left alt", DIK_LALT );
  _directXKeysMapString.emplace( "right win", DIK_RWIN );
  _directXKeysMapString.emplace( "left win", DIK_LWIN );
}

void Input::releaseDirectXInput() {
  if ( _directXInputKeyboard ) {
    _directXInputKeyboard->Unacquire();
    _logger.info( "Unacquired Keyboard Device" );

    _directXInputKeyboard->Release();
    _logger.info( "Released DirectX Input Keyboard Device" );
  }
  if ( _directXInput ) {
    _directXInput->Release();
    _logger.info( "Released DirectX Input" );
  }
}

bool Input::directXKeyDown( const int key ) const {
  return (_directXKeys[key] & 0x80) != 0;
}

bool Input::oldDirectXKeyDown( const int key ) const {
  return (_oldDirectXKeys[key] & 0x80) != 0;
}

int Input::toDirectXKey( const int code ) const {
  const auto it = _directXKeysMapInt.find( code );
  ALA_ASSERT(it != _directXKeysMapInt.end());
  const auto directXCode = it->second;
  return directXCode;
}

int Input::toDirectXKey( const std::string& keyName ) const {
  const auto it = _directXKeysMapString.find( keyName );
  ALA_ASSERT(it != _directXKeysMapString.end());
  const auto directXCode = it->second;
  return directXCode;
}
}

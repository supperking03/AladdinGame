#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include <aladdin.h>

class GameData
{
private:
  static GameData* __instance;
  GameData(){}
  std::map<std::string, std::string> _datas;
public:
  int getInt(const std::string &key) ;
  float getFloat(const std::string &key) ;
  std::string getString(const std::string &key) ;

  void setInt(const std::string& key, const int value);
  void setFloat(const std::string& key, const float value);
  void setString(const std::string& key, const std::string& value);

  bool keyExists(const std::string &key);

  static GameData* get();
};

#endif //!__GAME_DATA_H__
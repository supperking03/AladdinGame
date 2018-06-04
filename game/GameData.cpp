#include "GameData.h"

GameData* GameData::__instance = nullptr;

int GameData::getInt(const std::string& key) 
{
  return stoi(_datas[key]);
}

float GameData::getFloat(const std::string& key) 
{
  return stof(_datas[key]);
}

std::string GameData::getString(const std::string& key) 
{
  return _datas[key];
}

void GameData::setInt(const std::string& key, const int value)
{
  _datas[key] = std::to_string(value);
}

void GameData::setFloat(const std::string& key, const float value)
{
  _datas[key] = std::to_string(value);
}

void GameData::setString(const std::string& key, const std::string& value)
{
  _datas[key] = value;
}

bool GameData::keyExists(const std::string& key)
{
  return _datas.find(key) != _datas.end();
}

GameData* GameData::get()
{
  if(__instance == NULL)
  {
    __instance = new GameData;
  }

  return __instance;
}

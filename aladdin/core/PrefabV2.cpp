#include "PrefabV2.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(PrefabV2, ala::Prefab)

GameObject* PrefabV2::instantiateWithArgs( const std::string& serializedArgs, const std::string& name,
                                           const std::string& quadIndex ) const {
  return instantiateWithArgs( GameManager::get()->getRunningScene(), serializedArgs, name, quadIndex );
}

GameObject* PrefabV2::instantiateWithArgs( Scene* scene, const std::string& serializedArgs, const std::string& name,
                                           const std::string& quadIndex ) const {
  if ( isReleasing() || isReleased() ) return NULL;

  const auto object = new GameObject( scene, name, quadIndex );
  std::istringstream argsStream( serializedArgs );
  doInstantiate( object, argsStream );

  return object;
}

GameObject* PrefabV2::instantiateWithArgs( GameObject* parentObject, const std::string& serializedArgs,
                                           const std::string& name ) const {

  if ( isReleasing() || isReleased() ) return NULL;

  const auto object = new GameObject( parentObject, name );
  std::istringstream argsStream( serializedArgs );
  doInstantiate( object, argsStream );

  return object;

}

void PrefabV2::doInstantiate( GameObject* object ) const {
  std::istringstream argsStream;
  doInstantiate( object, argsStream );
}

int PrefabV2::nextInt( std::istringstream& stream ) {
  int v;
  stream >> v;
  return v;
}

char PrefabV2::nextChar( std::istringstream& stream ) {
  char v;
  stream >> v;
  return v;
}

float PrefabV2::nextFloat( std::istringstream& stream ) {
  float v;
  stream >> v;
  return v;
}

bool PrefabV2::nextBool( std::istringstream& stream ) {
  bool v;
  stream >> v;
  return v;
}

std::string PrefabV2::nextString( std::istringstream& stream ) {
  std::string v;
  stream >> v;
  return v;
}

std::string PrefabV2::nextLine( std::istringstream& stream ) {
  std::string v;
  std::getline( stream, v );
  LTRIM(v);
  RTRIM(v);
  return v;
}
}

#ifndef __ALADDIN_PREFAB_V2_H__
#define __ALADDIN_PREFAB_V2_H__

#include "Prefab.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(PrefabV2, ala::Prefab)
public:
  PrefabV2( const std::string& name )
    : Prefab( name ) {}

  GameObject* instantiateWithArgs( const std::string& serializedArgs,
                                   const std::string& name = "", const std::string& quadIndex = "" ) const;

  GameObject* instantiateWithArgs( Scene* scene, const std::string& serializedArgs,
                                   const std::string& name = "", const std::string& quadIndex = "" ) const;

  GameObject* instantiateWithArgs( GameObject* parentObject, const std::string& serializedArgs,
                                   const std::string& name = "" ) const;

protected:
  void doInstantiate( GameObject* object ) const override;

  virtual void doInstantiate( GameObject* object, std::istringstream& argsStream ) const = 0;

  static int nextInt( std::istringstream& stream );
  static char nextChar( std::istringstream& stream );
  static float nextFloat( std::istringstream& stream );
  static bool nextBool( std::istringstream& stream );
  static std::string nextString( std::istringstream& stream );
  static std::string nextLine( std::istringstream& stream );
};
}

#endif //!__ALADDIN_PREFAB_V2_H__

#ifndef __ALADDIN_PHYSICS_COLLISION_INFO_H__
#define __ALADDIN_PHYSICS_COLLISION_INFO_H__

#include "PhysicsInclude.h"
#include "Collider.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(CollisionInfo)
private:
  Collider* _colliderA;
  Collider* _colliderB;
  float _penetration;
  Vec2 _normal;
public:
  CollisionInfo( Collider* a = NULL, Collider* b = NULL, const float penetration = 0, const Vec2& normal = Vec2( 0, 0 ) );
  virtual ~CollisionInfo();

  void setColliderA( Collider* colliderA );
  void setColliderB( Collider* colliderB );
  void setPenetration( const float penetration );
  void setNormal( const Vec2& normal );

  Collider* getColliderA() const;
  Collider* getColliderB() const;
  float getPenetration() const;
  const Vec2& getNormal() const;

  bool hasSameColliders( const CollisionInfo& collisionInfo ) const;
};
}

#endif //!__ALADDIN_PHYSICS_COLLISION_INFO_H__

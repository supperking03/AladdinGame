#include "CollisionInfo.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(CollisionInfo)

CollisionInfo::CollisionInfo( Collider* a, Collider* b, const float penetration, const Vec2& normal ) {
  _colliderA = a;
  _colliderB = b;
  _penetration = penetration;
  _normal = normal;
}

CollisionInfo::~CollisionInfo() {}

void CollisionInfo::setColliderA( Collider* colliderA ) {
  _colliderA = colliderA;
}

void CollisionInfo::setColliderB( Collider* colliderB ) {
  _colliderB = colliderB;
}


void CollisionInfo::setPenetration( const float penetration ) {
  _penetration = penetration;
}

void CollisionInfo::setNormal( const Vec2& normal ) {
  _normal = normal;
}

Collider* CollisionInfo::getColliderA() const {
  return _colliderA;
}

Collider* CollisionInfo::getColliderB() const {
  return _colliderB;
}

float CollisionInfo::getPenetration() const {
  return _penetration;
}

const Vec2& CollisionInfo::getNormal() const {
  return _normal;
}

bool CollisionInfo::hasSameColliders( const CollisionInfo& collisionInfo ) const {
  return (collisionInfo._colliderA == _colliderA && collisionInfo._colliderB == _colliderB)
    || (collisionInfo._colliderA == _colliderB && collisionInfo._colliderB == _colliderA);
}
}

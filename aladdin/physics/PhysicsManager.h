#ifndef __ALADDIN_PHYSICS_PHYSICS_MANAGER_H__
#define __ALADDIN_PHYSICS_PHYSICS_MANAGER_H__

#include "PhysicsInclude.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "CollisionInfo.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(PhysicsManager, ala::Releasable)
private:
  static PhysicsManager* __instance;
  Logger _logger;

  std::vector<Rigidbody*> _rigidbodies;
  std::vector<Collider*> _colliders;

  bool getCollisionInfo(Collider* a, Collider* b, CollisionInfo& collisionInfo) const;

  std::vector<CollisionInfo> _lastCollidingPairs;
  std::vector<CollisionInfo> _currentCollidingPairs;
public:
  PhysicsManager();

  virtual ~PhysicsManager();

  static PhysicsManager* get();

  void update(const float delta);

  void release() override;

  void attach(Rigidbody* rigidbody);

  void detach(Rigidbody* rigidbody);

  void attach(Collider* collider);

  void detach(Collider* collider);

  bool isCollidedLastFrame(const CollisionInfo& collisionInfo);
};
}

#endif //!__ALADDIN_PHYSICS_PHYSICS_MANAGER_H__
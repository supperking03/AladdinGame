#include "PhysicsManager.h"
#include "../core/StdHelper.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_1(PhysicsManager, Releasable)

  PhysicsManager* PhysicsManager::__instance = NULL;

bool PhysicsManager::getCollisionInfo(Collider* colliderA, Collider* colliderB, CollisionInfo& collisionInfo) const {
  const auto a = colliderA->getGameObject();
  const auto b = colliderB->getGameObject();

  collisionInfo.setColliderA(colliderA);
  collisionInfo.setColliderB(colliderB);

  const auto rigidbodyA = a->getComponentT<Rigidbody>();
  const auto rigidbodyB = b->getComponentT<Rigidbody>();

  if (colliderA == NULL || colliderB == NULL || rigidbodyA == NULL || rigidbodyB == NULL) return false;

  auto rectA = colliderA->getBoundingRect();
  auto rectB = colliderB->getBoundingRect();

  auto n = Vec2(rectB.getMidX(), rectB.getMidY()) - Vec2(rectA.getMidX(), rectA.getMidY());

  const float aExtentX = rectA.getSize().getWidth() / 2;
  const float bExtentX = rectB.getSize().getWidth() / 2;

  const float xOverlap = aExtentX + bExtentX - abs(n.getX());

  if (xOverlap > 0) {
    const float aExtentY = rectA.getSize().getHeight() / 2;
    const float bExtentY = rectB.getSize().getHeight() / 2;

    const float yOverlap = aExtentY + bExtentY - abs(n.getY());

    if (yOverlap > 0) {
      if (xOverlap < yOverlap) {
        if (n.getX() < 0) {
          collisionInfo.setNormal(Vec2(-1, 0));
        }
        else {
          collisionInfo.setNormal(Vec2(1, 0));
        }

        collisionInfo.setPenetration(xOverlap);

        return true;
      }
      else {
        if (n.getY() < 0) {
          collisionInfo.setNormal(Vec2(0, -1));
        }
        else {
          collisionInfo.setNormal(Vec2(0, 1));
        }

        collisionInfo.setPenetration(yOverlap);

        return true;
      }
    }
  }

  return false;
}

PhysicsManager::PhysicsManager() :
  _logger("ala::PhysicsManager") {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  _logger.info("Created");
}

PhysicsManager::~PhysicsManager() {
  ALA_ASSERT(isReleased());
  _logger.info("Released");
}

PhysicsManager* PhysicsManager::get() {
  if (__instance == NULL) {
    __instance = new PhysicsManager;
  }
  return __instance;
}

void PhysicsManager::update(const float delta) {
  if (isReleasing() || isReleased()) return;

  //update transform position
  for (auto rigidbody : _rigidbodies) {
    rigidbody->getGameObject()->getTransform()->setPosition(rigidbody->getPosition());
  }

  std::map<int, std::vector<Collider*>> colliders;

  for (auto collider : _colliders) {
    const auto colliderList = colliders.find(collider->getPhysicsLayer());
    if (colliderList != colliders.end()) {
      colliders[collider->getPhysicsLayer()].push_back(collider);
    }
    else {
      std::vector<Collider*> addingCollider;
      addingCollider.push_back(collider);
      colliders[collider->getPhysicsLayer()] = addingCollider;
    }
  }

  for (auto layer : colliders) {
    for (auto itA = layer.second.begin(); itA != layer.second.end(); ++itA) {
      for (auto itB = itA + 1; itB != layer.second.end(); ++itB) {
        const auto colliderA = *itA;
        const auto colliderB = *itB;
        const auto gameObjectA = colliderA->getGameObject();
        const auto gameObjectB = colliderB->getGameObject();
        CollisionInfo collisionInfo;
        collisionInfo.setColliderA(colliderA);
        collisionInfo.setColliderB(colliderB);
        if (colliderA == colliderB) continue;
        if (!colliderA->isActive() || !colliderB->isActive())
        {
          if (colliderA->isTrigger() || colliderB->isTrigger()) {
            collisionInfo.setColliderA(colliderA);
            collisionInfo.setColliderB(colliderB);
            if (isCollidedLastFrame(collisionInfo)) {
              gameObjectA->onTriggerExit(collisionInfo);
              gameObjectB->onTriggerExit(collisionInfo);
            }
          }
          else {
            collisionInfo.setColliderA(colliderA);
            collisionInfo.setColliderB(colliderB);
            if (isCollidedLastFrame(collisionInfo)) {
              gameObjectA->onCollisionExit(collisionInfo);
              gameObjectB->onCollisionExit(collisionInfo);
            }
          }
          continue;
          
        }
        if (colliderA->isIgnoredBy(colliderB) || colliderB->isIgnoredBy(colliderA))
        {
          if (colliderA->isTrigger() || colliderB->isTrigger()) {
            collisionInfo.setColliderA(colliderA);
            collisionInfo.setColliderB(colliderB);
            if (isCollidedLastFrame(collisionInfo)) {
              gameObjectA->onTriggerExit(collisionInfo);
              gameObjectB->onTriggerExit(collisionInfo);
            }
          }
          else {
            collisionInfo.setColliderA(colliderA);
            collisionInfo.setColliderB(colliderB);
            if (isCollidedLastFrame(collisionInfo)) {
              gameObjectA->onCollisionExit(collisionInfo);
              gameObjectB->onCollisionExit(collisionInfo);
            }
          }
          continue;
        }


        if (gameObjectA == gameObjectB) continue;

        auto rigidbodyA = gameObjectA->getComponentT<Rigidbody>();
        auto rigidbodyB = gameObjectB->getComponentT<Rigidbody>();


        auto rectA = colliderA->getBoundingRect();
        auto rectB = colliderB->getBoundingRect();

        if (!getCollisionInfo(colliderA, colliderB, collisionInfo)) {
          if (colliderA->isTrigger() || colliderB->isTrigger()) {
            collisionInfo.setColliderA(colliderA);
            collisionInfo.setColliderB(colliderB);
            if (isCollidedLastFrame(collisionInfo)) {
              gameObjectA->onTriggerExit(collisionInfo);
              gameObjectB->onTriggerExit(collisionInfo);
            }
          }
          else {
            collisionInfo.setColliderA(colliderA);
            collisionInfo.setColliderB(colliderB);
            if (isCollidedLastFrame(collisionInfo)) {
              gameObjectA->onCollisionExit(collisionInfo);
              gameObjectB->onCollisionExit(collisionInfo);
            }
          }
          continue;
        }

        _currentCollidingPairs.push_back(collisionInfo);

        if (colliderA->isTrigger() || colliderB->isTrigger()) {
          if (!isCollidedLastFrame(collisionInfo)) {
            gameObjectA->onTriggerEnter(collisionInfo);
            gameObjectB->onTriggerEnter(collisionInfo);
          }

          gameObjectA->onTriggerStay(collisionInfo);
          gameObjectB->onTriggerStay(collisionInfo);

          continue;
        }

        if (!isCollidedLastFrame(collisionInfo)) {
          gameObjectA->onCollisionEnter(collisionInfo);
          gameObjectB->onCollisionEnter(collisionInfo);
        }

        gameObjectA->onCollisionStay(collisionInfo);
        gameObjectB->onCollisionStay(collisionInfo);


        const Vec2 relativeVelocity = rigidbodyB->getVelocity() - rigidbodyA->getVelocity();
        const float velocityAlongNormal = relativeVelocity.dot(collisionInfo.getNormal());

        //do not resolve if objects are seperating
        if (velocityAlongNormal > 0) {
          continue;
        }

        const float restitution = MIN(rigidbodyA->getPhysicsMaterial().getRestitution(),
          rigidbodyB->getPhysicsMaterial().getRestitution());

        float impulseScalar = -(1 + restitution) * velocityAlongNormal;
        impulseScalar /= rigidbodyA->getInverseMass() + rigidbodyB->getInverseMass();

        //apply impulse
        const Vec2 impulse = collisionInfo.getNormal() * impulseScalar;

        rigidbodyA->resetForce();
        rigidbodyB->resetForce();

        //positional correction
        const float percent = 0.2f; // usually 20% to 80%
        const float slop = 0.01f; // usually 0.01 to 0.1
        const Vec2 correction = collisionInfo.getNormal() * (MAX(collisionInfo.getPenetration() - slop, 0.0f) / (
          rigidbodyA->
          getInverseMass() + rigidbodyB->getInverseMass())) * percent;

        if (rigidbodyA->getBodyType() == ALA_BODY_TYPE_DYNAMIC) {
          rigidbodyA->setVelocity(rigidbodyA->getVelocity() - impulse * rigidbodyA->getInverseMass());

          rigidbodyA->setPosition(rigidbodyA->getPosition() - correction * rigidbodyA->getInverseMass());
        }

        if (rigidbodyB->getBodyType() == ALA_BODY_TYPE_DYNAMIC) {
          rigidbodyB->setVelocity(rigidbodyB->getVelocity() + impulse * rigidbodyB->getInverseMass());

          rigidbodyB->setPosition(rigidbodyB->getPosition() + correction * rigidbodyB->getInverseMass());
        }

        // TODO: Friction
      }
    }

    //update transform position
    for (auto rigidbody : _rigidbodies) {
      rigidbody->getGameObject()->getTransform()->setPosition(rigidbody->getPosition());
    }

    _lastCollidingPairs.clear();
    _lastCollidingPairs.insert(_lastCollidingPairs.begin(), _currentCollidingPairs.begin(),
      _currentCollidingPairs.end());
    _currentCollidingPairs.clear();
  }
}


void PhysicsManager::release() {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));

  setToReleasing();

  setToReleased();

  // destroy
  delete this;
}

void PhysicsManager::attach(Rigidbody* rigidbody) {
  if (isReleasing() || isReleased()) return;
  if (rigidbody == NULL) return;
  _rigidbodies.push_back(rigidbody);
}

void PhysicsManager::detach(Rigidbody* rigidbody) {
  if (isReleasing() || isReleased()) return;
  if (rigidbody == NULL) return;
  StdHelper::vectorErase(_rigidbodies, rigidbody);
}

void PhysicsManager::attach(Collider* collider) {
  if (isReleasing() || isReleased()) return;
  if (collider == NULL) return;
  _colliders.push_back(collider);
}

void PhysicsManager::detach(Collider* collider) {
  if (isReleasing() || isReleased()) return;
  if (collider == NULL) return;
  StdHelper::vectorErase(_colliders, collider);
}

bool PhysicsManager::isCollidedLastFrame(const CollisionInfo& collisionInfo) {
  for (const auto collision : _lastCollidingPairs) {
    if (collisionInfo.hasSameColliders(collision)) {
      return true;
    }

  }

  return false;
}
}

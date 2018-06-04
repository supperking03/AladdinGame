#ifndef __ALADDIN_PHYSICS_RIGID_BODY_H__
#define __ALADDIN_PHYSICS_RIGID_BODY_H__

#include "PhysicsInclude.h"
#include "PhysicsMaterial.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Rigidbody, ala::GameObjectComponent)
private:
  Vec2 _position;
  Vec2 _velocity;

  int _bodyType;
  
	PhysicsMaterial _material;

  float _gravityScale;

  Vec2 _forces;
  Vec2 _impulses;
public:
  Rigidbody(GameObject* gameObject, const PhysicsMaterial& material, const int bodyType = ALA_BODY_TYPE_DYNAMIC, const float gravityScale = 0, const std::string& name = "");

  void onPhysicsUpdate(const float delta) override;

	void resetForce();

  void addForce(const Vec2 &force);
  void addImpulse(const Vec2 &impulse);
	void addAcceleration(const Vec2& acceleration);
	void addVelocity(const Vec2& velocity);

  void setPosition(const Vec2& position);
  void setVelocity(const Vec2& velocity);
  void setBodyType(const int bodyType);
  void setGravityScale(const float gravityScale);
	void setPhysicsMaterial(const PhysicsMaterial& material);

  const Vec2& getPosition() const;
  const Vec2& getVelocity() const;
  int getBodyType() const;
	float getMass() const;
	float getInverseMass() const;
  float getGravityScale() const;
	const PhysicsMaterial& getPhysicsMaterial() const;

  void onInitialize() override;;

  void onRelease() override;

  virtual ~Rigidbody();
};
}
#endif //!__ALADDIN_PHYSICS_RIGID_BODY_H__
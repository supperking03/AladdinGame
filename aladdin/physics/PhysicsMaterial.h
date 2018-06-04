#ifndef __ALADDIN_PHYSICS_PHYSICS_MATERIAL_H__
#define __ALADDIN_PHYSICS_PHYSICS_MATERIAL_H__

#include "PhysicsInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(PhysicsMaterial)
private:
	float _density;
	float _restitution;
public:
	PhysicsMaterial(float density = 0, float restitution = 0);
	virtual ~PhysicsMaterial();

	void setDensity(float density);
	void setRestitution(float restitution);

	float getDensity() const;
	float getRestitution() const;
};
}


#endif //!__ALADDIN_PHYSICS_PHYSICS_MATERIAL_H__
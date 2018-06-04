#include "PhysicsMaterial.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(PhysicsMaterial)


PhysicsMaterial::PhysicsMaterial(const float density, const float restitution)
{
	_density = density;
	_restitution = restitution;
}

PhysicsMaterial::~PhysicsMaterial()
{
}

void PhysicsMaterial::setDensity(const float density)
{
	_density = density;
}

void PhysicsMaterial::setRestitution(const float restitution)
{
	_restitution = restitution;
}

float PhysicsMaterial::getDensity() const
{
	return _density;
}

float PhysicsMaterial::getRestitution() const
{
	return _restitution;
}
}

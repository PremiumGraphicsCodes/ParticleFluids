#include "KFBoundaryParticle.h"

#include "KFFluidScene.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

KFBoundaryParticle::KFBoundaryParticle(const double radius, const Vector3dd& position) :
	radius(radius),
	position(position)
{}

KFBoundaryParticle::~KFBoundaryParticle()
{
}

/*
float KFMacroParticle::getDensity() const
{
	return (microPoints.size()) / (double)selfCount;
	//return microCount / (double)(microCount + preCount);
}
*/
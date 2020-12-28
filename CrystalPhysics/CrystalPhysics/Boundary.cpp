#include "Boundary.h"

#include "../../Crystal/Math/Triangle3d.h"
#include "../../CrystalSpace/CrystalAlgo/MeshToParticleAlgo.h"

#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Algo;
using namespace Crystal::Physics;

void Boundary::build(const PolygonMesh& mesh, const double divideLength)
{
	const auto& positions = mesh.getPositions();
	const auto& faces = mesh.getFaces();

	MeshToParticleAlgo particleConverter;
	for (const auto& f : faces) {
		particleConverter.subdivide(f.toTriangle(positions), divideLength);
	}
	const auto& divPositions = particleConverter.getPositions();
	const auto& normals = particleConverter.getNormals();
	assert(divPositions.size() == normals.size());

	for (int i = 0; i < divPositions.size(); ++i) {
		Particle<BoundaryAttr> pn(divPositions[i], BoundaryAttr(normals[i]));	
		positionWithNormal.push_back(pn);
	}

}

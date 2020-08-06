#include "Boundary.h"

#include "../CrystalAlgo/MeshToParticleAlgo.h"

using namespace Crystal::Shape;
using namespace Crystal::Algo;
using namespace Crystal::Physics;

void Boundary::build(const PolygonMesh& mesh, const double divideLength)
{
	const auto& positions = mesh.getPositions();
	const auto& faces = mesh.getFaces();

	MeshToParticleAlgo particleConverter;
	//particleConverter.subdivide()
}

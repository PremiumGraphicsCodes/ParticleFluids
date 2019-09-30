#include "PolygonMeshAddCommand.h"

#include "../Scene/PolygonMeshScene.h"

#include "../Scene/PolygonMesh.h"
#include "../Scene/PolygonMeshBuilder.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

void PolygonMeshAddCommand::execute(World* scene)
{
	const auto& positions = args.positions.getValue();
	const auto& normals = args.normals.getValue();
	const auto& texCoords = args.texCoords.getValue();
	const auto& vertices = args.vertices.getValue();
	const auto& faces = args.faces.getValue();
	PolygonMesh* mesh = new PolygonMesh();
	for (const auto& p : positions) {
		mesh->createPosition(p);
	}
	for (const auto& n : normals) {
		mesh->createNormal(n);
	}
	for (const auto& tc : texCoords) {
		mesh->createTexCoord(tc);
	}
	for (const auto& v : vertices) {
		mesh->createVertex(v.positionId, v.normalId, v.texCoordId);
	}
	for (const auto& f : faces) {
		mesh->createFace(f.getV1(), f.getV2(), f.getV3());
	}

	auto shape = scene->getObjectFactory()->createPolygonMeshScene(mesh, args.name.getValue());
	const auto newId = shape->getId();

	results.newId.setValue(newId);
}

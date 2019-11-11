#include "PolygonMeshCreateBySurfaceCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Scene/PolygonMesh.h"
#include "../../Crystal/Scene/PolygonMeshBuilder.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

/*
PolygonMeshCreateBySurfaceCommand::Args::Args() :
	surfaces(PolygonMeshCreateLabels::PositionsLabel, {}),
	normals(PolygonMeshCreateLabels::NormalsLabel, {}),
	texCoords(PolygonMeshCreateLabels::TexCoordsLabel, {}),
	vertices(PolygonMeshCreateLabels::VerticesLabel, {}),
	faces(PolygonMeshCreateLabels::FacesLabel, {}),
	name(PolygonMeshCreateLabels::NameLabel, std::string(""))
{
	add(&positions);
	add(&normals);
	add(&texCoords);
	add(&vertices);
	add(&faces);
	add(&name);
}

PolygonMeshCreateBySurfaceCommand::Results::Results() :
	newId(PolygonMeshCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string PolygonMeshCreateBySurfaceCommand::getName()
{
	return ::PolygonMeshCreateLabels::CommandNameLabel;
}

void PolygonMeshCreateBySurfaceCommand::execute(World* scene)
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
*/
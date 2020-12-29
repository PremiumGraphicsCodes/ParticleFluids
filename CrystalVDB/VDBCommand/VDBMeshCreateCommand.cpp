#include "VDBMeshCreateCommand.h"

#include "../../CrystalVDB/VDBConverter/VDBPolygonMesh.h"

#include "PublicLabels/VDBMeshCreateLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

VDBMeshCreateCommand::Args::Args() :
	positions(::PositionsLabel, {}),
	triangleIndices(::TriangleIndicesLabel, {}),
	quadIndices(::QuadIndicesIdLabel, {})
{
	add(&positions);
	add(&triangleIndices);
	add(&quadIndices);
}

VDBMeshCreateCommand::Results::Results() :
	newId(::NewVDBMeshIdLabel, -1)
{
	add(&newId);
}

std::string VDBMeshCreateCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBMeshCreateCommand::execute(World* world)
{
	/*
	auto mesh = std::make_unique<PolygonMesh>();
	mesh->positions = args.positions.getValue();
	mesh->normals = args.normals.getValue();
	mesh->texCoords = args.texCoords.getValue();
	mesh->vertices = args.vertices.getValue();
	mesh->faces = args.faces.getValue();

	auto shape = new PolygonMeshScene(world->getNextSceneId(), args.name.getValue(), std::move(mesh));//world->getSceneFactory()->createPolygonMeshScene(std::move(mesh), args.name.getValue());
	world->addScene(args.layer.getValue(), shape);
	//auto group = (shape, "FaceGroup");
	const auto newId = shape->getId();

	results.newId.setValue(newId);
	*/

	return true;
}

#include "PolygonMeshAddVerticesCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "Public/PolygonMeshAddVerticesLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshAddVerticesCommand::Args::Args() :
	meshId(PolygonMeshAddVerticesLabels::PolygonMeshIdLabel, -1),
	positionsIds(PolygonMeshAddVerticesLabels::PositionIdsLabel, {}),
	normalIds(PolygonMeshAddVerticesLabels::NormalIdsLabel, {}),
	texCoordIds(PolygonMeshAddVerticesLabels::TexCoordIdsLabel, {})
{
	add(&meshId);
	add(&positionsIds);
	add(&normalIds);
	add(&texCoordIds);
}

PolygonMeshAddVerticesCommand::Results::Results()
{
}

std::string PolygonMeshAddVerticesCommand::getName()
{
	return ::PolygonMeshAddVerticesLabels::CommandNameLabel;
}

bool PolygonMeshAddVerticesCommand::execute(World* world)
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

	//world->updateViewModel();

	results.newId.setValue(newId);
	*/

	return true;
}

#include "PolygonMeshCreateCommand.h"

#include "../Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "Public/PolygonMeshCreateLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshCreateCommand::Args::Args() :
	positions(PolygonMeshCreateLabels::PositionsLabel, {}),
	normals(PolygonMeshCreateLabels::NormalsLabel, {}),
	texCoords(PolygonMeshCreateLabels::TexCoordsLabel, {}),
	vertices(PolygonMeshCreateLabels::VerticesLabel, {}),
	faces(PolygonMeshCreateLabels::FacesLabel, {}),
	name(PolygonMeshCreateLabels::NameLabel, std::string("")),
	layer(PolygonMeshCreateLabels::LayerLabel, 1)
{
	add(&positions);
	add(&normals);
	add(&texCoords);
	add(&vertices);
	add(&faces);
	add(&name);
	add(&layer);
}

PolygonMeshCreateCommand::Results::Results() :
	newId(PolygonMeshCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string PolygonMeshCreateCommand::getName()
{
	return ::PolygonMeshCreateLabels::CommandNameLabel;
}

bool PolygonMeshCreateCommand::execute(World* world)
{
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

	return true;
}

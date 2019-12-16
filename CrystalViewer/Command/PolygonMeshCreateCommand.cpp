#include "PolygonMeshCreateCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

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

void PolygonMeshCreateCommand::execute(World* world)
{
	auto mesh = new PolygonMesh();
	mesh->positions = args.positions.getValue();
	mesh->normals = args.normals.getValue();
	mesh->texCoords = args.texCoords.getValue();
	mesh->vertices = args.vertices.getValue();
	mesh->faces = args.faces.getValue();

	auto shape = world->getSceneFactory()->createPolygonMeshScene(mesh, args.name.getValue());
	world->addScene(args.layer.getValue(), shape);
	auto group = world->getSceneFactory()->createFaceGroupScene(shape, "FaceGroup");
	for (auto f : mesh->faces) {
		group->addFace(f);
	}
	//shape->addGroup(group);
	const auto newId = shape->getId();

	world->updateViewModel();

	results.newId.setValue(newId);
}

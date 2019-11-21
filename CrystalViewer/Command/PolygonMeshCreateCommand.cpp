#include "PolygonMeshCreateCommand.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Shape/PolygonMeshBuilder.h"

#include "Public/PolygonMeshCreateLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshCreateCommand::Args::Args() :
	positions(PolygonMeshCreateLabels::PositionsLabel, {}),
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

	auto shape = world->getObjectFactory()->createPolygonMeshScene(mesh, args.name.getValue());
	world->getObjects()->addScene(shape);
	const auto newId = shape->getId();

	world->updateViewModel();

	results.newId.setValue(newId);
}

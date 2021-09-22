#include "TriangleMeshCreateCommand.h"

#include "../../Crystal/Scene/TriangleMeshScene.h"

#include "../../Crystal/Shape/TriangleMesh.h"
#include "../../Crystal/Shape/TriangleMeshBuilder.h"

#include "Public/TriangleMeshCreateLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TriangleMeshCreateCommand::Args::Args() :
	triangles(TriangleMeshCreateLabels::TrianglesLabel, {}),
	name(TriangleMeshCreateLabels::NameLabel, std::string("")),
	layer(TriangleMeshCreateLabels::LayerLabel, 1)
{
	add(&triangles);
	add(&name);
	add(&layer);
}

TriangleMeshCreateCommand::Results::Results() :
	newId(TriangleMeshCreateLabels::NewIdLabel, -1)
{
	add(&newId);
}

std::string TriangleMeshCreateCommand::getName()
{
	return ::TriangleMeshCreateLabels::CommandNameLabel;
}

bool TriangleMeshCreateCommand::execute(World* world)
{
	const auto triangles = args.triangles.getValue();

	auto mesh = std::make_unique<TriangleMesh>();
	for (const auto& t : triangles) {
		const TriangleFace face(t);
		mesh->addFace(face);
	}

	auto shape = new TriangleMeshScene(world->getNextSceneId(), args.name.getValue(), std::move(mesh));//world->getSceneFactory()->createPolygonMeshScene(std::move(mesh), args.name.getValue());
	world->addScene(args.layer.getValue(), shape);
	const auto newId = shape->getId();

	results.newId.setValue(newId);

	return true;
}

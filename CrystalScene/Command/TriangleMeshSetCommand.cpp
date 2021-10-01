#include "TriangleMeshSetCommand.h"

#include "../Scene/TriangleMeshScene.h"

#include "Public/TriangleMeshSetLabels.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

TriangleMeshSetCommand::Args::Args() :
	meshId(TriangleMeshSetLabels::MeshIdLabel, -1),
	triangles(TriangleMeshSetLabels::TrianglesLabel, {})
{
	add(&meshId);
	add(&triangles);
}

TriangleMeshSetCommand::Results::Results()
{
}

std::string TriangleMeshSetCommand::getName()
{
	return TriangleMeshSetLabels::CommandNameLabel;
}

bool TriangleMeshSetCommand::execute(World* world)
{
	const auto scene = world->getScenes()->findSceneById<TriangleMeshScene*>(args.meshId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto& triangles = args.triangles.getValue();

	auto shape = std::make_unique<TriangleMesh>();
	for (const auto& t : triangles) {
		shape->addFace(TriangleFace(t));
	}
	scene->setShape(std::move(shape));

	return true;
}

#include "PolygonMeshAddFacesCommand.h"

#include "../../Crystal/Shape/PolygonMesh.h"
#include "../../Crystal/Scene/PolygonMeshScene.h"

#include "Public/PolygonMeshAddFacesLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PolygonMeshAddFacesCommand::Args::Args() :
	meshId(PolygonMeshAddFacesLabels::PolygonMeshIdLabel, -1),
	vertexIds(PolygonMeshAddFacesLabels::VertexIdsLabel, {})
{
	add(&meshId);
	add(&vertexIds);
}

PolygonMeshAddFacesCommand::Results::Results()
{
}

std::string PolygonMeshAddFacesCommand::getName()
{
	return ::PolygonMeshAddFacesLabels::CommandNameLabel;
}

bool PolygonMeshAddFacesCommand::execute(World* world)
{
	auto scene = world->getScenes()->findSceneById<PolygonMeshScene*>(args.meshId.getValue());
	auto shape = scene->getShape();
	const auto vertexIds = args.vertexIds.getValue();

	/*
	for (int i = 0; i < positionIds.size(); ++i) {
		Vertex v;
		v.positionId = positionIds[i];
		v.normalId = normalIds[i];
		v.texCoordId = texCoordIds[i];
		shape->vertices.push_back(v);
	}
	*/

	return true;
}

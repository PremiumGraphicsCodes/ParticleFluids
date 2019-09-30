#include "PolygonMeshAddCommand.h"

#include "../Scene/PolygonMesh.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;

void PolygonMeshAddCommand::execute(World* scene)
{
	const auto& positions = args.positions.getValue();
	const auto& normals = args.normals.getValue();
	const auto& texCoords = args.texCoords.getValue();
	const auto& vertices = args.vertices.getValue();
	/*

	auto faces = mesh->Faces;
	std::vector<Crystal::Scene::Face> fs;
	for (int i = 0; i < faces->Count; ++i) {
		auto f = faces[i];
		dest->createFace(f->V0, f->V1, f->V2);
	}
	auto str = msclr::interop::marshal_as<std::string>(name);
	auto scene = factory->createPolygonMeshScene(dest, str);
	instance->addScene(scene);
	return scene->getId();

	/*
	PolygonMesh* mesh = new PolygonMesh();
	mesh->createPosition()
	scene->getObjectFactory()->createPolygonMeshScene();
	scene->getObjects()->addScene()
	*/
}

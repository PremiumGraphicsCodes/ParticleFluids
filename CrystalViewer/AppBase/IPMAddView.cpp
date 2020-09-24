#include "IPMAddView.h"

#include "../Command/Command.h"
#include "../Command/Public/CameraLabels.h"

#include "../../Crystal/Scene/PolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

IPMAddView::IPMAddView(const std::string& name, World* model, Canvas* canvas) :
	IOkCancelView(name, model, canvas),
	matrixView("Matrix", Math::Identity()),
	nameView("Name", "PolygonMesh01")
//	attributeView("PSAttribute")
{
	add(&matrixView);
	add(&nameView);
}

void IPMAddView::addPolygonMesh(const PolygonMeshBuilder& builder)
{
	auto world = getWorld();
	auto mesh = std::make_unique<PolygonMesh>();
	mesh->positions = builder.getPositions();
	mesh->normals = builder.getNormals();
	mesh->texCoords = builder.getTexCoords();
	mesh->vertices = builder.getVertices();
	mesh->faces = builder.getFaces();

	auto shape = new PolygonMeshScene(world->getNextSceneId(), nameView.getValue(), std::move(mesh));//world->getSceneFactory()->createPolygonMeshScene(std::move(mesh), args.name.getValue());
	world->getScenes()->addScene(shape);
	auto group = new FaceGroupScene(world->getNextSceneId(), "FaceGroup", shape);
	shape->addGroup(group);
	const auto& faces = shape->getShape()->faces;
	for (auto f : faces) {
		group->addFace(f);
	}
	const auto newId = shape->getId();

	auto scene = getWorld()->getScenes()->findSceneById<PolygonMeshScene*>(newId);
	auto controller = scene->getPresenter();
	controller->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
	//getWorld()->getRenderer()->getScene()->screen.addChild(controller.getView());

}
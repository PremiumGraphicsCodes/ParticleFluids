#include "FaceGroupEditView.h"

#include "../../Crystal/Scene/FaceGroupScene.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

FaceGroupEditView::FaceGroupEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	world(repository),
	id("Id"),
	name("Name"),
	edit("Edit")
{
	edit.setFunction([=]() { onEdit(); });
}

void FaceGroupEditView::onShow()
{
	id.show();
	name.show();
	edit.show();
}

void FaceGroupEditView::setValue(FaceGroupScene* value)
{
	id.setValue(value->getId());
	name.setValue(value->getName());
}

void FaceGroupEditView::onEdit()
{
	/*
	auto polygonMesh = world->getObjects()->findSceneById<PolygonMeshScene*>(id.getValue());
	polygonMesh->setName(name.getValue());
	*/
}
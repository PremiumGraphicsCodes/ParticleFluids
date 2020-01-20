#include "FaceGroupEditView.h"

#include "../../Crystal/Scene/FaceGroupScene.h"
#include "../../Crystal/Scene/World.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

FaceGroupEditView::FaceGroupEditView(const std::string& name, World* repository, Canvas* canvas) :
	IWindow(name),
	world(repository),
	id("Id"),
	name("Name"),
	materialName("MaterialName"),
	edit("Edit")
{
	edit.setFunction([=]() { onEdit(); });
}

void FaceGroupEditView::onShow()
{
	id.show();
	name.show();
	materialName.show();
	edit.show();
}

void FaceGroupEditView::setValue(FaceGroupScene* value)
{
	id.setValue(value->getId());
	name.setValue(value->getName());
//	materialName.setValue(value->getMaterial().getName());
}

void FaceGroupEditView::onEdit()
{
	auto faceGroup = world->getObjects()->findSceneById<FaceGroupScene*>(id.getValue());
	faceGroup->setName(name.getValue());
//	faceGroup->setMaterialName(materialName.getValue());
}
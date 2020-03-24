#include "FaceGroupEditView.h"

#include "../../Crystal/Scene/FaceGroupScene.h"
#include "../../Crystal/Scene/MaterialScene.h"
#include "../../Crystal/Scene/World.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

FaceGroupEditView::FaceGroupEditView(const std::string& name, World* world, Canvas* canvas) :
	IEditCancelView(name, world, canvas),
	idView("Id"),
	nameView("Name"),
	materialNameView("Material")
{
	add(&idView);
	add(&nameView);
	add(&materialNameView);
}

void FaceGroupEditView::setValue(FaceGroupScene* value)
{
	idView.setValue(value->getId());
	nameView.setValue(value->getName());
	if (value->getMaterial() != nullptr) {
		materialNameView.setValue(value->getMaterial()->getName());
	}
}

void FaceGroupEditView::onEdit()
{
	auto faceGroup = getWorld()->getObjects()->findSceneById<FaceGroupScene*>(idView.getValue());
	faceGroup->setName(nameView.getValue());
	auto material = getWorld()->getObjects()->findSceneByName<MaterialScene*>(materialNameView.getValue());
	faceGroup->setMaterial(material);
}
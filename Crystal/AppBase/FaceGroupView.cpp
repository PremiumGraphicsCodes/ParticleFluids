#include "FaceGroupView.h"

#include "../Shape/Face.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::UI;

FaceGroupView::FaceGroupView(const std::string& name) :
	IWindow(name),
	id("Id"),
	faceCount("Faces"),
	materialName("Material")
{
}

FaceGroupView::FaceGroupView(const std::string& name, FaceGroupScene* value) :
	IWindow(name),
	id("Id", value->getId()),
	faceCount("Faces", value->getShape().size()),
	materialName("Material", value->getMaterialName())
{
}

void FaceGroupView::show()
{
	id.show();
	faceCount.show();
	materialName.show();
}

void FaceGroupView::setValue(FaceGroupScene* value)
{
	id.setValue(value->getId());
	faceCount.setValue(value->getShape().size());
	materialName.setValue(value->getMaterialName());
}

#include "FaceGroupView.h"

#include "../Shape/Face.h"
#include "../Shape/FaceFactory.h"

using namespace Crystal::Shape;
using namespace Crystal::UI;

FaceGroupView::FaceGroupView(const std::string& name) :
	IWindow(name),
	id("Id"),
	faceCount("Faces"),
	attributeId("AttributeId")
{
}

FaceGroupView::FaceGroupView(const std::string& name, const FaceGroup& value) :
	IWindow(name),
	id("Id", value.id),
	faceCount("Faces"),
	attributeId("AttributeId", value.attributeId)
{
}

void FaceGroupView::show()
{
	id.show();
	faceCount.show();
	attributeId.show();
}

void FaceGroupView::setValue(const FaceGroup& value)
{
	id.setValue(value.id);
	faceCount.setValue(value.faces.size());
	attributeId.setValue(value.attributeId);
}

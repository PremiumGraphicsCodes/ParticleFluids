#pragma once

#include "IOkCancelView.h"
#include "Matrix4dView.h"
#include "StringView.h"

#include "../../Crystal/Shape/PolygonMeshBuilder.h"

namespace Crystal {
	namespace UI {

class IPMAddView : public IOkCancelView
{
public:
	IPMAddView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void addPolygonMesh(const Shape::PolygonMeshBuilder& builder);

private:
	Matrix4dView matrixView;
	StringView nameView;
	//PSAttributeView attributeView;
};

	}
}
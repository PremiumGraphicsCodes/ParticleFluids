#pragma once

#include "IOkCancelView.h"
#include "WFAttributeView.h"
#include "Matrix4dView.h"
#include "../../Crystal/Shape/WireFrameEdge.h"

namespace Crystal {
	namespace UI {

class IWFAddView : public IOkCancelView
{
public:
	IWFAddView(const std::string& name, Scene::World* model, Canvas* canvas) :
		IOkCancelView(name, model, canvas),
		attributeView("WFAttribute"),
		matrixView("Matrix", Math::Identity()),
		nameView("Name", "WireFrame01")
	{
		add(&attributeView);
		add(&matrixView);
		add(&nameView);
	}

protected:
	void addWireFrame(const std::vector<Math::Vector3dd>& positions, const std::vector<Shape::WireFrameEdge>& edges);

private:
	WFAttributeView attributeView;
	Matrix4dView matrixView;
	StringView nameView;
};

	}
}
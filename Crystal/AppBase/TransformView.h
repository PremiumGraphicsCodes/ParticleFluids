#pragma once

#include "IPanel.h"
#include "Vector3dView.h"
#include "Matrix3dView.h"

namespace Crystal {
	namespace UI {

class TransformView : public IPanel
{
public:
	TransformView(const std::string& name, Scene::World* model, Canvas* canvas);

	void onShow() override;

private:
	Vector3dView translate;
	Matrix3dView rotation;
};

	}
}
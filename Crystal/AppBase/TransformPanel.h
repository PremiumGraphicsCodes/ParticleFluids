#pragma once

#include "IPanel.h"
#include "Vector3dView.h"

namespace Crystal {
	namespace UI {

class TransformPanel : public IPanel
{
public:
	TransformPanel(const std::string& name, Repository* model, Canvas* canvas);

private:
	Vector3dView translate;
};

	}
}
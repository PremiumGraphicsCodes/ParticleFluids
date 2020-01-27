#pragma once

#include "IOkCancelView.h"

#include "Quad3dView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMQuadView : public IOkCancelView
{
public:
	PMQuadView(const std::string& name, Scene::World* world, Canvas* canvas);

private:
	void onOk() override;

private:
	Quad3dView quadView;
	StringView nameView;
};

	}
}

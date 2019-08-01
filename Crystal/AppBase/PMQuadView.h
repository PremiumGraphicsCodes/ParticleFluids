#pragma once

#include "IOkCancelView.h"

#include "Quad3dView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PMQuadView : public IOkCancelView
{
public:
	PMQuadView(Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk() override;

private:
	Quad3dView quad;
	StringView materialName;
	StringView name;
};

	}
}

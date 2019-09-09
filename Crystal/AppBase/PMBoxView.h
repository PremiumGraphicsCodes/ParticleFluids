#pragma once
#include "IOkCancelView.h"

#include "Box3dView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PMBoxView : public IOkCancelView
{
public:
	PMBoxView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Box3dView boxView;
	StringView name;
};

	}
}
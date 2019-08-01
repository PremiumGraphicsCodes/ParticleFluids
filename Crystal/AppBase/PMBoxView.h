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
	PMBoxView(Scene::RootScene* model, Canvas* canvas);

private:
	void show() override;

	void onOk() override;

private:
	Box3dView boxView;
	StringView materialName;
	StringView name;
};

	}
}
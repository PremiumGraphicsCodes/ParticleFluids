#pragma once

#include "IPanel.h"

#include "Quad3dView.h"
#include "IntView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PMQuadView : public IPanel
{
public:
	PMQuadView(Repository* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Quad3dView quad;
	StringView materialName;
	StringView name;
	Button ok;
};

	}
}

#pragma once

#include "IPanel.h"

#include "Box3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "BoolView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSBoxView : public IPanel
{
public:
	PSBoxView(Repository* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Box3dView box;
	PSAttributeView attribute;
	IntView count;
	BoolView isVolume;
	StringView name;
	Button ok;
};

	}
}
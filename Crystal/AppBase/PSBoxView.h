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
	PSBoxView(Repository* model, Canvas* canvas) :
		IPanel("PSBox", model, canvas),
		box("Box"),
		attribute("Attribute"),
		count("Count", 10000),
		isVolume("Volume", false),
		okButton("OK")
	{
	};

	void show() override;

	void onOk();

private:
	Box3dView box;
	PSAttributeView attribute;
	IntView count;
	BoolView isVolume;
	Button okButton;
};

	}
}
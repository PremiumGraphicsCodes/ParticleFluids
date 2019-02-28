#include "IPopupButton.h"

#include "Cylinder3dView.h"
#include "PSAttributeView.h"

namespace Crystal {
	namespace UI {

class PSCylinderButton : public IPopupButton
{
public:
	PSCylinderButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSCylinder", model, canvas),
		attribute("Attribute"),
		cylinderButton("Cylinder")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{
	}

private:
	Cylinder3dView cylinderButton;
	PSAttributeView attribute;

	int count = 10000;
};

	}
}
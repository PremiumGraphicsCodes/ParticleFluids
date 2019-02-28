#include "IPopupButton.h"

#include "Cylinder3dView.h"

namespace Crystal {
	namespace UI {

class PSCylinderButton : public IPopupButton
{
public:
	PSCylinderButton(Repository* model, Canvas* canvas) :
		IPopupButton("PSCylinder", model, canvas),
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

	float size = 1.0f;

	int count = 10000;
};

	}
}
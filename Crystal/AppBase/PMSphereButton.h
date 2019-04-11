#pragma once

#include "IPopupButton.h"
#include "Sphere3dView.h"
#include "PMAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PMSphereButton : public IPopupButton
{
public:
	PMSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("PMSphere", model, canvas),
		sphereView("Sphere"),
		unumView("UNum", 36),
		vnumView("VNum", 36),
		materialId("MaterialId", 1),
		name("Name", "PMSphere")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Sphere3dView sphereView;
	IntView unumView;
	IntView vnumView;
	IntView materialId;
	StringView name;
};

	}
}
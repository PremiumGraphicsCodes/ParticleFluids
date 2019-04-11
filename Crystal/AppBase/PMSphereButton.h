#pragma once

#include "IPopupButton.h"
#include "Sphere3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMSphereButton : public IPopupButton
{
public:
	PMSphereButton(Repository* model, Canvas* canvas) :
		IPopupButton("PMSphere", model, canvas),
		sphere("Sphere"),
		unum("UNum", 36),
		vnum("VNum", 36),
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
	Sphere3dView sphere;
	IntView unum;
	IntView vnum;
	IntView materialId;
	StringView name;
};

	}
}
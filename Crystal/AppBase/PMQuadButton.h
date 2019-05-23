#pragma once

#include "IPopupButton.h"

#include "Quad3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMQuadButton : public IPopupButton
{
public:
	PMQuadButton(Repository* model, Canvas* canvas);

	void onShow();

	void onOk();

	void onCancel();

private:
	Quad3dView quad;
	IntView materialId;
	StringView name;
};

	}
}

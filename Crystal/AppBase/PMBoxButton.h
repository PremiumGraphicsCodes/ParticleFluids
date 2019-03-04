#include "IPopupButton.h"

#include "Box3dView.h"

namespace Crystal {
	namespace UI {

class PMBoxButton : public IPopupButton
{
public:
	PMBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("PMBox", model, canvas),
		boxView("Box")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Box3dView boxView;
};

	}
}
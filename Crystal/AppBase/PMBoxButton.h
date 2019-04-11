#include "IPopupButton.h"

#include "Box3dView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class PMBoxButton : public IPopupButton
{
public:
	PMBoxButton(Repository* model, Canvas* canvas) :
		IPopupButton("PMBox", model, canvas),
		boxView("Box"),
		materialId("MaterialId", 1),
		name("Name", "PMBox")
	{
	}

	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}

private:
	Box3dView boxView;
	IntView materialId;
	StringView name;
};

	}
}
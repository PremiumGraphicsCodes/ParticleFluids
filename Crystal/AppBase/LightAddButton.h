#include "IPopupButton.h"

#include "LightView.h"

namespace Crystal {
	namespace UI {

class LightAddButton : public IPopupButton
{
public:
	LightAddButton(Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	LightView light;
	StringView name;
};

	}
}
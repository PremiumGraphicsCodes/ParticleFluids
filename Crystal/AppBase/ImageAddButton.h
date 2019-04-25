#include "IPopupButton.h"

#include "ImageView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class ImageAddButton : public IPopupButton
{
public:
	ImageAddButton(const std::string& name, Repository* model, Canvas* canvas);

	void onShow() override;

	void onOk() override;

	void onCancel() override;

private:
	ImageView image;
	StringView name;
};

	}
}
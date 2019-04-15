#include "IPopupButton.h"

#include "Vector3dView.h"
#include "Float4View.h"
#include "StringView.h"

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
	Vector3dView position;
	Float4View ambient;
	Float4View diffuse;
	Float4View specular;
	StringView name;
};

	}
}
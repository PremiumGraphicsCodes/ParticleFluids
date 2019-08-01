#include "IPanel.h"

#include "Cylinder3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class PSCylinderView : public IPanel
{
public:
	PSCylinderView(RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	Cylinder3dView cylinderButton;
	PSAttributeView attribute;
	IntView count;
	Button ok;
};

	}
}
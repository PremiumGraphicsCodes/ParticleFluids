#include "IOkCancelView.h"

#include "Cylinder3dView.h"
#include "PSAttributeView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSCylinderView : public IOkCancelView
{
public:
	PSCylinderView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Cylinder3dView cylinder;
	PSAttributeView attribute;
	IntView count;
};

	}
}
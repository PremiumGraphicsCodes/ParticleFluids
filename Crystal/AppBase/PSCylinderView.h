#include "IPSAddView.h"

#include "Cylinder3dView.h"
#include "IntView.h"

namespace Crystal {
	namespace UI {

class PSCylinderView : public IPSAddView
{
public:
	PSCylinderView(Scene::World* model, Canvas* canvas);

private:
	void onOk() override;

private:
	Cylinder3dView cylinder;
	IntView count;
};

	}
}
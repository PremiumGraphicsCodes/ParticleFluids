#include "IOkCancelView.h"

#include "LightView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class LightAddView : public IOkCancelView
{
public:
	LightAddView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk();

private:
	LightView light;
	StringView name;
};

	}
}
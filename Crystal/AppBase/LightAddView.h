#include "IPanel.h"

#include "LightView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class LightAddView : public IPanel
{
public:
	LightAddView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	LightView light;
	StringView name;
	Button ok;
};

	}
}
#include "IPanel.h"

#include "TextureView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class TextureAddView : public IPanel
{
public:
	TextureAddView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void show() override;

private:
	void onOk();

private:
	TextureView image;
	StringView name;
	Button ok;
};

	}
}
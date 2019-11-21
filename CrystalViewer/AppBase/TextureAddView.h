#include "IPanel.h"

#include "TextureView.h"
#include "StringView.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class TextureAddView : public IPanel
{
public:
	TextureAddView(const std::string& name, Scene::World* model, Canvas* canvas);

	void onShow() override;

private:
	void onOk();

private:
	TextureView image;
	StringView name;
	StringView filePathView;
	Button ok;
};

	}
}
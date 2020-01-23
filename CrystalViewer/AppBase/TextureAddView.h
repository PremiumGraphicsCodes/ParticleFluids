#include "IOkCancelView.h"

#include "FilePathView.h"

namespace Crystal {
	namespace UI {

class TextureAddView : public IOkCancelView
{
public:
	TextureAddView(const std::string& name, Scene::World* model, Canvas* canvas);

private:
	void onOk();

private:
	//TextureView image;
	FilePathView filePathView;
	StringView nameView;
};

	}
}
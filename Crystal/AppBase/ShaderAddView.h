#pragma once

#include "IOkCancelView.h"
#include "ShaderView.h"

namespace Crystal {
	namespace UI {

class ShaderAddView : public IOkCancelView
{
public:
	ShaderAddView(const std::string& name, Scene::RootScene* model, Canvas* canvas);

	void show() override;

protected:
	void onOk() override;

private:
	ShaderView shader;
};

	}
}

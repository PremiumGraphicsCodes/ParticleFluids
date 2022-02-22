#pragma once

#include "CrystalScene/AppBase/IOkCancelView.h"

namespace Crystal {
	namespace UI {

// Compute Shader sample.
class CSSampleView : public IOkCancelView
{
public:
	CSSampleView(const std::string& name, Scene::World* model, Canvas* canvas);

protected:
	void onOk() override;

private:
};

	}
}
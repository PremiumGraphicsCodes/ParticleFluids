#pragma once

#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class IOkCancelView : public IPanel
{
public:
	IOkCancelView(const std::string& name, Scene::RootScene* scene, Canvas* canvas) :
		IPanel(name, scene, canvas),
		ok("Ok"),
		cancel("Cancel")
	{
		ok.setFunction([=]() { onOk(); });
		cancel.setFunction([=]() { onCancel(); });
	}

	void show() override
	{
		ok.show();
		cancel.show();
	}

	virtual void onOk() = 0;

	virtual void onCancel() {};

private:
	Button ok;
	Button cancel;
};

	}
}
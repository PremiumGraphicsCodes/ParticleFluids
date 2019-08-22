#pragma once

#include "IPanel.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class IOkCancelView : public IPanel
{
public:
	IOkCancelView(const std::string& name, Scene::World* scene, Canvas* canvas) :
		IPanel(name, scene, canvas),
		ok("Ok"),
		cancel("Cancel")
	{
		ok.setFunction([=]() { onOk(); });
		cancel.setFunction([=]() { onCancel(); });
	}

	virtual ~IOkCancelView() {}

	void show() override
	{
		onShow();
		ok.show();
		cancel.show();
	}

protected:
	virtual void onShow() {};

	virtual void onOk() = 0;

	virtual void onCancel() {};

private:
	Button ok;
	Button cancel;
};

	}
}
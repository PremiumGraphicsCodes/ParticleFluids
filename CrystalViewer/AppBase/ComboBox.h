#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class ComboBox : public IWindow
{
public:
	explicit ComboBox(const std::string& name) :
		IWindow(name)
	{}

	//~Button()
	//{}

	void onShow() override;

private:
//	std::function<void(void)> func;
};
	}
}
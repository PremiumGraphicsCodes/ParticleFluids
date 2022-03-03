#pragma once

#include "IWindow.h"
#include <functional>

namespace Crystal {
	namespace UI {

class MenuItem : public IWindow
{
public:
	explicit MenuItem(const std::string& name) :
		IWindow(name)
	{}

	~MenuItem()
	{}

	void onShow() override;

protected:
	virtual void onPushed() = 0;

private:
};

	}
}
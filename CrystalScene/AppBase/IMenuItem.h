#pragma once

#include "IWindow.h"
#include <functional>

namespace Crystal {
	namespace UI {

class IMenuItem : public IWindow
{
public:
	explicit IMenuItem(const std::string& name) :
		IWindow(name)
	{}

	~IMenuItem()
	{}

	void onShow() override;

protected:
	virtual void onPushed() = 0;

private:
};

	}
}
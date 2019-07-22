#pragma once

#include "IWindow.h"
#include <functional>

namespace Crystal {
	namespace UI {

class Button : public IWindow
{
public:
	explicit Button(const std::string& name) :
		IWindow(name)
	{}

	~Button()
	{}

	void show() override;

	void setFunction(std::function<void(void)> func) {
		this->func = std::move(func);
	}

private:
	std::function<void(void)> func;
};
	}
}
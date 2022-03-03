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

class MenuItem : public IMenuItem
{
public:
	explicit MenuItem(const std::string& name) :
		IMenuItem(name)
	{}

	MenuItem(const std::string& name, std::function<void()> func) :
		IMenuItem(name),
		func(func)
	{}

	~MenuItem()
	{}

	void setFunction(std::function<void(void)> func) {
		this->func = std::move(func);
	}

protected:
	void onPushed() override {
		this->func();
	}

private:
	std::function<void(void)> func;
};

	}
}
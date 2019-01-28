#pragma once

#include <list>

namespace Crystal {
	namespace UI {

class IWindow
{
protected:
	explicit IWindow(const std::string& name) :
		name(name)
	{}

	virtual ~IWindow() {
		for (auto c : children) {
			delete c;
		}
	};

public:
	void add(IWindow* child) { children.push_back(child); }

	virtual void show() = 0;

protected:
	std::string name;
	std::list<IWindow*> children;

};
	}
}
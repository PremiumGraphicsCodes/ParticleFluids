#pragma once

#include <list>

namespace Crystal {
	namespace UI {

class IWindow
{
protected:
	virtual ~IWindow() {
		for (auto c : children) {
			delete c;
		}
	};

public:
	virtual void show() = 0;

protected:
	std::list<IWindow*> children;

};
	}
}
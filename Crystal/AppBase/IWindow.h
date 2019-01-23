#pragma once

namespace Crystal {
	namespace UI {

class IWindow
{
protected:
	virtual ~IWindow() {};

public:
	virtual void show() = 0;
};
	}
}
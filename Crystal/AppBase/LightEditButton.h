#pragma once

#include "IWindow.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"
#include "../Model/LightObject.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class LightEditButton : public IWindow
{
public:
	LightEditButton(const std::string& name, Repository* repository, Canvas* canvas);

	void setValue(const LightObject& value) {
		this->id.setValue(value.getId());
		this->light.setValue(*value.getLight());
		this->name.setValue(value.getName());
	}

	void show() override;
/*
	void onShow() override;

	void onOk() override;

	void onCancel() override
	{

	}
	*/

private:
	IntView id;
	LightView light;
	StringView name;
	Repository* repository;
	Canvas* canvas;
};

	}
}

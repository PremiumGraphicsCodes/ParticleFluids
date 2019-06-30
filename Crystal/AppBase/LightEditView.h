#pragma once

#include "IWindow.h"
#include "LightView.h"
#include "IntView.h"
#include "StringView.h"
#include "../Scene/LightScene.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

namespace Crystal {
	namespace UI {

class LightEditView : public IWindow
{
public:
	LightEditView(const std::string& name, Repository* repository, Canvas* canvas);

	void setValue(const Model::LightScene& value) {
		this->id.setValue(value.getId());
		this->light.setValue(*value.getLight());
		this->name.setValue(value.getName());
	}

	void show() override;

	//void setVisible(const bool isVisible) { this->isVisible = isVisible; }

private:
	IntView id;
	LightView light;
	StringView name;
	Repository* repository;
	Canvas* canvas;
};

	}
}

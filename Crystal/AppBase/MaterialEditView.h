#pragma once

#include "IPopupButton.h"
#include "MaterialView.h"
#include "IntView.h"
#include "StringView.h"

namespace Crystal {
	namespace UI {

class MaterialEditView : public IWindow
{
public:
	MaterialEditView(const std::string& name, Repository* model, Canvas* canvas);

	void setValue(Model::MaterialScene* value)
	{
//		int id, const Graphics::Material& material, const std::string& name) {
		this->id.setValue(value->getId());
		//this->material.setValue(*value->getMaterial());
		this->name.setValue( value->getName() );
	}

	void show() override;

	/*
	void onOk() override;

	void onCancel() override
	{

	}
	*/

private:
	IntView id;
	MaterialView material;
	StringView name;
	Repository* repository;
	Canvas* canvas;
};

	}
}

#pragma once

#include "IPopupButton.h"

namespace Crystal {
	namespace UI {

class FaceSelectButton : public IPopupButton
{
public:
	FaceSelectButton(const std::string& name, Repository* model, Canvas* canvas) :
		IPopupButton(name, model, canvas),
		id(0),
		type(Model::ObjectType::All)
	{
	}

	FaceSelectButton(const std::string& name, Repository* model, Canvas* canvas, const Model::ObjectType type) :
		IPopupButton(name, model, canvas),
		id(0),
		type(type)
	{
	}


	void onShow() override;

	void onOk() override;

	void onCancel() override;

	int getId() const { return id; }

private:
	int id;
	Model::ObjectType type;
};

	}
}
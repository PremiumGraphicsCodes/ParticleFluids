#pragma once

#include "IWindow.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "../Model/TextureObjectRepository.h"

namespace Crystal {
	namespace UI {

class ImageView : public IWindow
{
public:
	ImageView(const std::string& name, Model::TextureObjectRepository& repository,  const int textureId) :
		IWindow(name),
		repository(repository),
		textureId(textureId)
	{}

	void setTextureId(const int id) { this->textureId = id; }

	void show() override;

/*
	std::string getValue() const { return value; }

	void setValue(const std::string& value) { this->value = value; }
	*/

private:
	Model::TextureObjectRepository& repository;
	int textureId;
};

	}
}
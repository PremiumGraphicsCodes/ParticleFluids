#pragma once

/*
#include "IWindow.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "../Shader/TextureObjectRepository.h"

namespace Crystal {
	namespace UI {

class TextureView : public IWindow
{
public:
	TextureView(const std::string& name, Shader::TextureObjectRepository& repository,  const int textureId) :
		IWindow(name),
		repository(repository),
		textureId(textureId)
	{}

	void setTextureId(const int id) { this->textureId = id; }

	void show() override;

	std::string getValue() const { return value; }

	void setValue(const std::string& value) { this->value = value; }

private:
	Shader::TextureObjectRepository& repository;
	int textureId;
};

	}
}
*/
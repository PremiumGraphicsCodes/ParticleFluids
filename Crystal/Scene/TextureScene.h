#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Scene {

class TextureScene : public IScene
{
public:
	TextureScene(const int id, const std::string& name, Shader::TextureObject* texture) :
		IScene(id, name),
		texture(texture)
	{}

	~TextureScene() {};

	Shader::TextureObject* getTexture() const { return texture; }

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	bool isNull() const { return texture == nullptr; }

	SceneType getType() const override { return SceneType::TextureScene; }

	void onClear() override
	{
		delete texture;
	}

private:
	Shader::TextureObject* texture;
};

	}
}
#pragma once

#include "IScene.h"
#include "../Shader/TextureObject.h"

namespace Crystal {
	namespace Model {

class TextureObject : public IScene
{
public:
	TextureObject(const int id, const std::string& name, Shader::TextureObject* texture) :
		IScene(id, name),
		texture(texture)
	{}

	~TextureObject() {};

	Shader::TextureObject* getTexture() const { return texture; }

	//void setMaterial(const Graphics::Material& material) { this->material = material; }

	void transform(const Math::Matrix3dd& m) { ; }

	void transform(const Math::Matrix4dd& m) { ; }

	bool isNull() const { return texture == nullptr; }

	SceneType getType() const override { return SceneType::TextureObject; }

	void onClear() override
	{
		delete texture;
	}

private:
	Shader::TextureObject* texture;
};

	}
}
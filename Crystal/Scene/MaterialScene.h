#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"
#include "MaterialController.h"
#include <memory>

namespace Crystal {
	namespace Scene {
		class TextureScene;

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, std::unique_ptr<Graphics::Material> material);

	~MaterialScene() {};

	Graphics::Material* getMaterial() { return material.get(); }

	SceneType getType() const override { return SceneType::MaterialScene; }

	IController* getController() override { return &controller; }
	
private:
	std::unique_ptr<Graphics::Material> material;
	MaterialController controller;
};

	}
}
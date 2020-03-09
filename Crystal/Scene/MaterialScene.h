#pragma once

#include "IScene.h"
#include "../Graphics/Material.h"
#include <memory>

namespace Crystal {
	namespace Scene {
		class TextureScene;

class MaterialScene : public IScene
{
public:
	MaterialScene(const int id, const std::string& name, std::unique_ptr<Graphics::Material> material, const int materialId);

	~MaterialScene() {};

	Graphics::Material* getMaterial() { return material.get(); }

	void onClear() override {};

	SceneType getType() const override { return SceneType::MaterialScene; }

	void send(SceneViewModel& viewModel) override;
	
	int getMaterialId() const { return materialId; }

private:
	std::unique_ptr<Graphics::Material> material;
	const int materialId;
};

	}
}